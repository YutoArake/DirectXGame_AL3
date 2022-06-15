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
	
	#pragma region ワールドトランスフォームの初期化

	//親(キャラクターの大元)
	worldTransforms_[kRoot].Initialize();
	//子(脊椎)
	worldTransforms_[kSpine].Initialize();
	worldTransforms_[kSpine].translation_ = {0.0f, 0.0f, 0.0f};
	worldTransforms_[kSpine].parent_ = &worldTransforms_[kRoot];
	
	//子(上半身)
	//胸
	worldTransforms_[kChest].Initialize();
	worldTransforms_[kChest].translation_ = {0.0f, 0.0f, 0.0f};
	worldTransforms_[kChest].parent_ = &worldTransforms_[kSpine];
	//頭
	worldTransforms_[kHead].Initialize();
	worldTransforms_[kHead].translation_ = {0.0f, 3.0f, 0.0f};
	worldTransforms_[kHead].parent_ = &worldTransforms_[kChest];
	//左腕
	worldTransforms_[kArmL].Initialize();
	worldTransforms_[kArmL].translation_ = {-3.0f, 0.0f, 0.0f};
	worldTransforms_[kArmL].parent_ = &worldTransforms_[kChest];
	//右腕
	worldTransforms_[kArmR].Initialize();
	worldTransforms_[kArmR].translation_ = {3.0f, 0.0f, 0.0f};
	worldTransforms_[kArmR].parent_ = &worldTransforms_[kChest];

	//子(下半身)
	//尻
	worldTransforms_[kHip].Initialize();
	worldTransforms_[kHip].translation_ = {0.0f, -3.0f, 0.0f};
	worldTransforms_[kHip].parent_ = &worldTransforms_[kSpine];
	//左足
	worldTransforms_[kLegL].Initialize();
	worldTransforms_[kLegL].translation_ = {-3.0f, -3.0f, 0.0f};
	worldTransforms_[kLegL].parent_ = &worldTransforms_[kHip];
	//右足
	worldTransforms_[kLegR].Initialize();
	worldTransforms_[kLegR].translation_ = {3.0f, -3.0f, 0.0f};
	worldTransforms_[kLegR].parent_ = &worldTransforms_[kHip];
	#pragma endregion

	#pragma region viewProjectionの設定
	//カメラ視点座標を設定
	viewProjection_.eye = {0.0f, 0.0f, -50.0f};

	//カメラ注視点座標を設定
	viewProjection_.target = {0.0f, 0.0f, 0.0f};

	//カメラ上方向ベクトルを設定(右上45度指定)
	//viewProjection_.up = {0.0f, 0.0f, 0.0f};

	//カメラ垂直方向視野角を設定
	//viewProjection_.fovAngleY = RadianTransform(45.0f);

	//アスペクト比を設定
	//viewProjection_.aspectRatio = 1.0f;

	//ニアクリップ距離を設定
	//viewProjection_.nearZ = 52.0f;
	
	//ファークリップ距離を設定
	//viewProjection_.farZ = 53.0f;

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

	//キャラクターの移動処理
	{
		//キャラクターの移動ベクトル
		Vector3 move = {0.0f, 0.0f, 0.0f};

		//キャラクターの移動速さ
		const float kPlayerSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_RIGHT)) {
			move.x += kPlayerSpeed;
		} else if (input_->PushKey(DIK_LEFT)) {
			move.x -= kPlayerSpeed;
		}

		//キャラクター移動（ベクトルの加算）
		worldTransforms_[kRoot].translation_ += move;

		//デバック用表示
		debugText_->SetPos(50.0f, 50.0f);
		debugText_->Printf(
		  "Root:(%f,%f,%f)", worldTransforms_[kRoot].translation_.x,
		  worldTransforms_[kRoot].translation_.y, worldTransforms_[kRoot].translation_.z);
	}

	//キャラクターの回転処理
	//上半身回転処理
	{
		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_U)) {
			//胸パーツのY軸周りの角度を減少
			worldTransforms_[kChest].rotation_ -= {0.0f, PI / 180, 0.0f};
		} else if (input_->PushKey(DIK_I)) {
			//胸パーツのY軸周りの角度を減少
			worldTransforms_[kChest].rotation_ += {0.0f, PI / 180, 0.0f};
		}
	}
	//下半身回転処理
	{
		//押した方向で移動ベクトルを変更
		if (input_->PushKey(DIK_J)) {
			//尻パーツのY軸周りの角度を減少
			worldTransforms_[kHip].rotation_ -= {0.0f, PI / 180, 0.0f};
		} else if (input_->PushKey(DIK_K)) {
			//尻パーツのY軸周りの角度を減少
			worldTransforms_[kHip].rotation_ += {0.0f, PI / 180, 0.0f};
		}
	}

	//子の更新
	{ 
		for (int i = 0; i < kNumPartId; i++) {
			worldTransforms_[i].UpdateWorldTransform(worldTransforms_[i], mat[i]);
		}
	}

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
	//	  "eye:(%f,%f,%f)", viewProjection_.eye.x, viewProjection_.eye.y, viewProjection_.eye.z);
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
	//	  "target:(%f,%f,%f)", viewProjection_.target.x, viewProjection_.target.y, viewProjection_.target.z);
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
	
	for (int i = kChest; i < kNumPartId; i++) {
		model_->Draw(worldTransforms_[i], viewProjection_, textureHandle_);
	}

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
