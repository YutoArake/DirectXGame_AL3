#include "GameScene.h"
#include "TextureManager.h"
#include <cassert>
#include "PrimitiveDrawer.h"
#include "AxisIndicator.h"
#include <math.h>

//円周率π
const float PI = 3.141592f;

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
}

void GameScene::Initialize() {

	dxCommon_ = DirectXCommon::GetInstance();
	input_ = Input::GetInstance();
	audio_ = Audio::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ファイル名を指定してテクスチャを読み込む
	textureHandle_ = TextureManager::Load("mario.jpg");

	// 3Dモデルの生成
	model_ = Model::Create();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	
	#pragma region アフィン変換

	//X, Y, Z方向のスケーリングを設定
	worldTransform_.scale_ = {2, 2, 2};
	//スケーリング行列を設定
	Matrix4 matScale;
	//スケーリング倍率を行列に設定する
	matScale = {
	  worldTransform_.scale_.x, 0.0f, 0.0f, 0.0f,
	  0.0f, worldTransform_.scale_.y, 0.0f, 0.0f,
	  0.0f, 0.0f, worldTransform_.scale_.z, 0.0f,
	  0.0f, 0.0f, 0.0f, 1.0f
	};

	//行列の計算
	for (int i = 0; i < 8; i++) {
		scaleVertex[i].x = vertex[i].x * matScale.m[0][0] + vertex[i].y * matScale.m[1][0] +
		                   vertex[i].z * matScale.m[2][0];
		scaleVertex[i].y = vertex[i].x * matScale.m[0][1] + vertex[i].y * matScale.m[1][1] +
		                   vertex[i].z * matScale.m[2][1];
		scaleVertex[i].z = vertex[i].x * matScale.m[0][2] + vertex[i].y * matScale.m[1][2] +
		                   vertex[i].z * matScale.m[2][2];
	}

	//単位行列を代入
	/*worldTransform_.matWorld_ = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};*/

	//行列の掛け算

	//行列の転送
	//worldTransform_.TransferMatrix();

	//X, Y, Z軸周りの回転角を設定
	worldTransform_.rotation_ = {0.0f, 0.0f, PI / 4};
	//合成用回転行列を宣言
	Matrix4 matRot;
	//各軸用回転行列を宣言
	Matrix4 matRotX, matRotY, matRotZ;

	//X軸回転行列の各要素を設定する
	matRotX = {
	  1.0f, 0.0f, 0.0f, 0.0f,
	  0.0f, cos(worldTransform_.rotation_.x), sin(worldTransform_.rotation_.x), 0.0f,
	  0.0f, -sin(worldTransform_.rotation_.x), cos(worldTransform_.rotation_.x), 0.0f,
	  0.0f, 0.0f, 0.0f, 1.0f
	};
	// Y軸回転行列の各要素を設定する
	matRotY = {
	  cos(worldTransform_.rotation_.y), 0.0f, -sin(worldTransform_.rotation_.y), 0.0f,
	  0.0f, 1.0f, 0.0f, 0.0f,
	  sin(worldTransform_.rotation_.y), 0.0f, cos(worldTransform_.rotation_.y), 0.0f,
	  0.0f, 0.0f, 0.0f, 1.0f
	};
	// Z軸回転行列の各要素を設定する
	matRotZ = {
	  cos(worldTransform_.rotation_.z), sin(worldTransform_.rotation_.z), 0.0f, 0.0f,
	  -sin(worldTransform_.rotation_.z), cos(worldTransform_.rotation_.z), 0.0f, 0.0f,
	  0.0f, 0.0f, 1.0f, 0.0f,
	  0.0f, 0.0f, 0.0f, 1.0f
	};

	//各軸の回転行列を合成

	//行列の計算
	matRot = matRotZ;
	for (int i = 0; i < 8; i++) {
		rotateVertex[i].x = vertex[i].x * matRot.m[0][0] + vertex[i].y * matRot.m[1][0] + vertex[i].z * matRot.m[2][0];
		rotateVertex[i].y = vertex[i].x * matRot.m[0][1] + vertex[i].y * matRot.m[1][1] + vertex[i].z * matRot.m[2][1];
		rotateVertex[i].z = vertex[i].x * matRot.m[0][2] + vertex[i].y * matRot.m[1][2] + vertex[i].z * matRot.m[2][2];
	}

	//X, Y, Z軸周りの平行移動を設定
	worldTransform_.translation_ = {2.0f, 2.0f, 2.0f};
	//平行移動行列を宣言
	Matrix4 matTrans = MathUtility::Matrix4Identity();
	//移動量を行列に設定する
	matTrans = {
	  1.0f,
	  0.0f,
	  0.0f,
	  0.0f,
	  0.0f,
	  1.0f,
	  0.0f,
	  0.0f,
	  0.0f,
	  0.0f,
	  1.0f,
	  0.0f,
	  worldTransform_.translation_.x,
	  worldTransform_.translation_.y,
	  worldTransform_.translation_.z,
	  1.0f
	};

	for (int i = 0; i < 8; i++) {
		translateVertex[i].x = vertex[i].x * matTrans.m[0][0] + vertex[i].y * matTrans.m[1][0] + vertex[i].z * matTrans.m[2][0] + 1 * matTrans.m[3][0];
		translateVertex[i].y = vertex[i].x * matTrans.m[0][1] + vertex[i].y * matTrans.m[1][1] + vertex[i].z * matTrans.m[2][1] + 1 * matTrans.m[3][1];
		translateVertex[i].z = vertex[i].x * matTrans.m[0][2] + vertex[i].y * matTrans.m[1][2] + vertex[i].z * matTrans.m[2][2] + 1 * matTrans.m[3][2];
	}
	#pragma endregion

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 960);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//ライン描画が参照するビュープロジェクションを指定する（アドレス渡し）
	PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());
}

void GameScene::Update() {
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
	model_->Draw(worldTransform_, debugCamera_->GetViewProjection(), textureHandle_);
	
	/// 線の立方体描画
	for (int i = 0; i < 12; i++) {
		PrimitiveDrawer::GetInstance()->DrawLine3d(vertex[edgeList[i][0]], vertex[edgeList[i][1]], white);
		PrimitiveDrawer::GetInstance()->DrawLine3d(scaleVertex[edgeList[i][0]], scaleVertex[edgeList[i][1]], red);
		PrimitiveDrawer::GetInstance()->DrawLine3d(rotateVertex[edgeList[i][0]], rotateVertex[edgeList[i][1]], blue);
		PrimitiveDrawer::GetInstance()->DrawLine3d(translateVertex[edgeList[i][0]], translateVertex[edgeList[i][1]], green);
	}

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
