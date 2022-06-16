#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <random>

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;

	//自キャラの解放
	delete player_;

	// delete debugCamera_;
}

void GameScene::Initialize() {

#pragma region 乱数生成
	//乱数シード生成器
	std::random_device seed_gen;
	//メルセンヌ・ツイスターの乱数エンジン
	std::mt19937_64 engine(seed_gen());

	//乱数範囲の設定(角度)
	std::uniform_real_distribution<float> distAngle(0.0f, PI);

	//乱数範囲の設定(座標)
	std::uniform_real_distribution<float> distPos(-10.0f, 10.0f);
#pragma endregion

	//インスタンス生成
	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	// 3Dモデルの生成
	model_ = Model::Create();

	//自キャラの生成
	player_ = new Player();

	//自キャラの初期化
	player_->Initialize(model_, textureHandle_);

#pragma region viewProjectionの設定
	//カメラ視点座標を設定
	viewProjection_.eye = {0.0f, 0.0f, -50.0f};

	//カメラ注視点座標を設定
	viewProjection_.target = {0.0f, 0.0f, 0.0f};

	//カメラ上方向ベクトルを設定(右上45度指定)
	// viewProjection_.up = {0.0f, 0.0f, 0.0f};

	//カメラ垂直方向視野角を設定
	// viewProjection_.fovAngleY = RadianTransform(45.0f);

	//アスペクト比を設定
	// viewProjection_.aspectRatio = 1.0f;

	//ニアクリップ距離を設定
	// viewProjection_.nearZ = 52.0f;

	//ファークリップ距離を設定
	// viewProjection_.farZ = 53.0f;

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
#pragma endregion

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 960);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&viewProjection_);
}

void GameScene::Update() {
	//自キャラの更新
	player_->Update();

#pragma region viewProjectionの各種移動処理
	//視点移動処理
	{
		//	//視点の移動ベクトル
		//	Vector3 move = {0.0f, 0.0f, 0.0f};

		//	//視点の移動速さ
		//	const float kEyeSpeed = 0.2f;

		//	//押した方向で移動ベクトルを変更
		//	if (input_->PushKey(DIK_W)) {
		//		move.z += kEyeSpeed;
		//	} else if (input_->PushKey(DIK_S)) {
		//		move.z -= kEyeSpeed;
		//	}

		//	//視点移動（ベクトルの加算）
		//	viewProjection_.eye += move;

		//	//行列の再計算
		//	viewProjection_.UpdateMatrix();

		//	//デバック用表示
		//	debugText_->SetPos(50.0f, 50.0f);
		//	debugText_->Printf(
		//	  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y,
		//viewProjection_.eye.z);
		//}

		////注視点移動処理
		//{
		//	//視点の移動ベクトル
		//	Vector3 move = {0.0f, 0.0f, 0.0f};

		//	//視点の移動速さ
		//	const float kTargetSpeed = 0.2f;

		//	//押した方向で移動ベクトルを変更
		//	if (input_->PushKey(DIK_LEFT)) {
		//		move.x -= kTargetSpeed;
		//	} else if (input_->PushKey(DIK_RIGHT)) {
		//		move.x += kTargetSpeed;
		//	}

		//	//視点移動（ベクトルの加算）
		//	viewProjection_.target += move;

		//	//行列の再計算
		//	viewProjection_.UpdateMatrix();

		//	//デバック用表示
		//	debugText_->SetPos(50.0f, 70.0f);
		//	debugText_->Printf(
		//	  "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y,
		//viewProjection_.target.z);
		//}

		////上方向回転処理
		//{
		//	//上方向の回転速さ[ラジアン/frame]
		//	const float kUpRotSpeed = 0.05f;

		//	//押した方向で移動ベクトルを変更
		//	if (input_->PushKey(DIK_SPACE)) {
		//		viewAngle += kUpRotSpeed;
		//		//2πを超えたら0に戻す
		//		viewAngle = fmodf(viewAngle, PI * 2.0f);
		//	}

		//	//上方向ベクトルを計算（半径1の円周上の座標）
		//	viewProjection_.up = {cosf(viewAngle), sinf(viewAngle), 0.0f};

		//	//行列の再計算
		//	viewProjection_.UpdateMatrix();

		//	//デバック用表示
		//	debugText_->SetPos(50.0f, 90.0f);
		//	debugText_->Printf(
		//	  "up:(%f,%f,%f)", viewProjection_.up.x, viewProjection_.up.y, viewProjection_.up.z);
		//}

		////Fov変更処理
		//{
		//	//上キーで視野角が広がる
		//	if (input_->PushKey(DIK_UP)) {
		//		viewProjection_.fovAngleY += 0.02f;
		//		//πを超えないようにする
		//		viewProjection_.fovAngleY = min(max(viewProjection_.fovAngleY, 0.01f), PI);
		//		//下キーで視野角が狭まる
		//	} else if (input_->PushKey(DIK_DOWN)) {
		//		viewProjection_.fovAngleY -= 0.02f;
		//		//0.01を下回らないようにする
		//		viewProjection_.fovAngleY = min(max(viewProjection_.fovAngleY, 0.01f), PI);
		//	}

		//	//行列の再計算
		//	viewProjection_.UpdateMatrix();

		//	//デバック用表示
		//	debugText_->SetPos(50.0f, 110.0f);
		//	debugText_->Printf("fovAngleY(Degree):%f", DegreeTransform(viewProjection_.fovAngleY));
		//}

		////クリップ距離変更処理
		//{
		//	//SHIFT,CTRLでニアクリップ距離を増減
		//	if (input_->PushKey(DIK_LSHIFT)) {
		//		viewProjection_.nearZ += 0.2f;
		//		//下キーで視野角が狭まる
		//	} else if (input_->PushKey(DIK_LCONTROL)) {
		//		viewProjection_.nearZ -= 0.2f;
		//	}

		//	//行列の再計算
		//	viewProjection_.UpdateMatrix();

		//	//デバック用表示
		//	debugText_->SetPos(50.0f, 130.0f);
		//	debugText_->Printf("nearZ:%f", viewProjection_.nearZ);
	}
#pragma endregion

	//デバッグカメラの処理
#ifdef _DEBUG
	if (input_->TriggerKey(DIK_SPACE)) {
		//デバックカメラ有効フラグをトグル
		isDebugCameraActive = !isDebugCameraActive;
	}
#endif // DEBUG

	if (isDebugCameraActive) {
		//デバッグカメラの更新
		debugCamera_->Update();
		viewProjection_.matView = debugCamera_->GetViewProjection().matView;
		viewProjection_.matProjection = debugCamera_->GetViewProjection().matProjection;
		viewProjection_.TransferMatrix();
	} else {
		viewProjection_.UpdateMatrix();
		viewProjection_.TransferMatrix();
	}

	//デバック用表示
	debugText_->SetPos(50.0f, 70.0f);
	debugText_->Printf("isDebugCamera SPACE ON/OF");
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

	player_->Draw(viewProjection_);

	//範囲forで全てのワールドトランスフォームを順に処理する

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
