#include "GameScene.h"
#include "TextureManager.h"
#include "AxisIndicator.h"
#include <cassert>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());

	//乱数範囲の設定(角度)
	std::uniform_real_distribution<float> distAngle(0.0f, PI);

	//乱数範囲の設定(座標)
	std::uniform_real_distribution<float> distPos(-10.0f, 10.0f);

	//インスタンス生成
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	// 3Dモデルの生成
	model_ = Model::Create();

	//範囲forで全てのワールドトランスフォームを順に処理する
	for (WorldTransform& worldTransform : worldTransforms_) {
		//ワールドトランスフォームの初期化
		worldTransform.Initialize();

#pragma region アフィン変換

#pragma region 拡縮
		// X, Y, Z方向のスケーリングを設定
		worldTransform.scale_ = {1.0f, 1.0f, 1.0f};

		//スケーリング行列を宣言
		Matrix4 matScale;

		//スケーリング倍率を行列に設定する
		GenerateScaleMatrix(worldTransform, matScale);

#pragma endregion

#pragma region 回転
		// X, Y, Z軸周りの回転角を設定
		worldTransform.rotation_ = {distAngle(engine), distAngle(engine), distAngle(engine)};

		//合成用回転行列を宣言
		Matrix4 matRot;

		//各軸用回転行列を宣言
		Matrix4 matRotX, matRotY, matRotZ;

		// X, Y, Z軸回転行列の各要素を設定する
		GenerateRotateXMatrix(worldTransform, matRotX);
		GenerateRotateYMatrix(worldTransform, matRotY);
		GenerateRotateZMatrix(worldTransform, matRotZ);

		//各軸の回転行列を合成
		matRot = MatrixCalculation(MatrixCalculation(matRotZ, matRotX), matRotY);

#pragma endregion

#pragma region 平行移動
		// X, Y, Z軸周りの平行移動を設定
		worldTransform.translation_ = {distPos(engine), distPos(engine), distPos(engine)};

		//平行移動行列を宣言
		Matrix4 matTrans;

		//移動量を行列に設定する
		GenerateTransformMatrix(worldTransform, matTrans);

#pragma endregion
		//単位行列を代入
		GenerateIdentityMatrix(worldTransform.matWorld_);

		//行列の合成(scale * rot * transの順番)
		worldTransform.matWorld_ = MatrixCalculation(worldTransform.matWorld_, matScale);
		worldTransform.matWorld_ = MatrixCalculation(worldTransform.matWorld_, matRot);
		worldTransform.matWorld_ = MatrixCalculation(worldTransform.matWorld_, matTrans);

		//行列の転送
		worldTransform.TransferMatrix();

#pragma endregion

	}
	
	//カメラ視点座標を設定
	viewProjection_.eye = {0.0f, 0.0f, -50.0f};

	//カメラ注視点座標を設定
	viewProjection_.target = {10.0f, 0.0f, 0.0f};

	//カメラ上方向ベクトルを設定(右上45度指定)
	viewProjection_.up = {cosf(PI / 4.0f), sinf(PI / 4.0f), 0.0f};

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 960);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	//視点移動処理
	{
		//視点の移動ベクトル
		Vector3 move = {0.0f, 0.0f, 0.0f};

		//視点の移動速さ
		const float kEyeSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_W)) {
			move.z += kEyeSpeed;
		} else if (input_->PushKey(DIK_S)) {
			move.z -= kEyeSpeed;
		}

		//視点移動（ベクトルの加算）
		viewProjection_.eye += move;

		//行列の再計算
		viewProjection_.UpdateMatrix();

		//デバック用表示
		debugText_->SetPos(50.0f, 50.0f);
		debugText_->Printf(
		  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
	}

	//注視点移動処理
	{
		//視点の移動ベクトル
		Vector3 move = {0.0f, 0.0f, 0.0f};

		//視点の移動速さ
		const float kTargetSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_LEFT)) {
			move.x -= kTargetSpeed;
		} else if (input_->PushKey(DIK_RIGHT)) {
			move.x += kTargetSpeed;
		}

		//視点移動（ベクトルの加算）
		viewProjection_.target += move;

		//行列の再計算
		viewProjection_.UpdateMatrix();

		//デバック用表示
		debugText_->SetPos(50.0f, 70.0f);
		debugText_->Printf(
		  "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
	}

	//上方向回転処理
	{
		//上方向の回転速さ[ラジアン/frame]
		const float kUpRotSpeed = 0.05f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_SPACE)) {
			viewAngle += kUpRotSpeed;
			//2πを超えたら0に戻す
			viewAngle = fmodf(viewAngle, PI * 2.0f);
		}

		//上方向ベクトルを計算（半径1の円周上の座標）
		viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};

		//行列の再計算
		viewProjection_.UpdateMatrix();

		//デバック用表示
		debugText_->SetPos(50.0f, 90.0f);
		debugText_->Printf(
		  "target:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
	}

	//デバッグカメラの更新
	debugCamera_->Update();
}

void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	
	//範囲forで全てのワールドトランスフォームを順に処理する
	for (WorldTransform& worldTransform : worldTransforms_) {
		model_->Draw(worldTransform, viewProjection_, textureHandle_);
	}
	
	/// 線の立方体描画
	
	/// </summary>

	// 3Dオブジェクト描画後処理
	Model::PostDraw();
	
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	// デバッグテキストの描画
	debugText_->DrawAll(commandList);
	//
	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}
