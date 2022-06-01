#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include "PrimitiveDrawer.h"
#include <cassert>
#include <math.h>

//円周率π
const float PI = 3.141592f;

//プロトタイプ宣言ここから
Matrix4 MatrixCalculation(WorldTransform worldTransform_, Matrix4 matScale);
Matrix4 TranslateMatrixCalculation(WorldTransform worldTransform_, Matrix4 matTrans);
Matrix4 RotateMatrixCalculation(Matrix4 matRot1, Matrix4 matRot2);

//プロトタイプ宣言ここまで

GameScene::GameScene() {}

GameScene::~GameScene() {
	delete model_;
	delete debugCamera_;
	//自キャラの解放
	delete player_;
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

	//ビュープロジェクションの初期化
	viewProjection_.Initialize();
	
	#pragma region アフィン変換

	#pragma region 拡縮
	////X, Y, Z方向のスケーリングを設定
	//worldTransform_.scale_ = {5, 2, 2};
	////スケーリング行列を設定
	//Matrix4 matScale;
	////スケーリング倍率を行列に設定する
	//matScale = {
	//  worldTransform_.scale_.x, 0.0f, 0.0f, 0.0f,
	//  0.0f, worldTransform_.scale_.y, 0.0f, 0.0f,
	//  0.0f, 0.0f, worldTransform_.scale_.z, 0.0f,
	//  0.0f, 0.0f, 0.0f, 1.0f
	//};

	////単位行列を代入
	//worldTransform_.matWorld_ = MathUtility::Matrix4Identity();

	////行列の掛け算
	//worldTransform_.matWorld_ = MatrixCalculation(worldTransform_, matScale);

	////行列の転送
	//worldTransform_.TransferMatrix();

	////行列の計算（Line描画）
	//for (int i = 0; i < 8; i++) {
	//	scaleVertex[i].x = vertex[i].x * matScale.m[0][0] + vertex[i].y * matScale.m[1][0] +
	//	                   vertex[i].z * matScale.m[2][0];
	//	scaleVertex[i].y = vertex[i].x * matScale.m[0][1] + vertex[i].y * matScale.m[1][1] +
	//	                   vertex[i].z * matScale.m[2][1];
	//	scaleVertex[i].z = vertex[i].x * matScale.m[0][2] + vertex[i].y * matScale.m[1][2] +
	//	                   vertex[i].z * matScale.m[2][2];
	//}
	#pragma endregion

	#pragma region 回転
	////X, Y, Z軸周りの回転角を設定
	//worldTransform_.rotation_ = {0.0f, 0.0f, PI / 4};
	////合成用回転行列を宣言
	//Matrix4 matRot;
	////各軸用回転行列を宣言
	//Matrix4 matRotX, matRotY, matRotZ;

	////X軸回転行列の各要素を設定する
	//matRotX = {
	//  1.0f, 0.0f, 0.0f, 0.0f,
	//  0.0f, cos(worldTransform_.rotation_.x), sin(worldTransform_.rotation_.x), 0.0f,
	//  0.0f, -sin(worldTransform_.rotation_.x), cos(worldTransform_.rotation_.x), 0.0f,
	//  0.0f, 0.0f, 0.0f, 1.0f
	//};
	//// Y軸回転行列の各要素を設定する
	//matRotY = {
	//  cos(worldTransform_.rotation_.y), 0.0f, -sin(worldTransform_.rotation_.y), 0.0f,
	//  0.0f, 1.0f, 0.0f, 0.0f,
	//  sin(worldTransform_.rotation_.y), 0.0f, cos(worldTransform_.rotation_.y), 0.0f,
	//  0.0f, 0.0f, 0.0f, 1.0f
	//};
	//// Z軸回転行列の各要素を設定する
	//matRotZ = {
	//  cos(worldTransform_.rotation_.z), sin(worldTransform_.rotation_.z), 0.0f, 0.0f,
	//  -sin(worldTransform_.rotation_.z), cos(worldTransform_.rotation_.z), 0.0f, 0.0f,
	//  0.0f, 0.0f, 1.0f, 0.0f,
	//  0.0f, 0.0f, 0.0f, 1.0f
	//};

	////各軸の回転行列を合成
	//matRot = RotateMatrixCalculation(RotateMatrixCalculation(matRotZ, matRotX), matRotY);

	////単位行列を代入
	////worldTransform_.matWorld_ = MathUtility::Matrix4Identity();

	////行列の計算
	//worldTransform_.matWorld_ = MatrixCalculation(worldTransform_, matRot);

	////行列の転送
	//worldTransform_.TransferMatrix();

	////行列の計算（Line描画）
	//for (int i = 0; i < 8; i++) {
	//	rotateVertex[i].x = vertex[i].x * matRot.m[0][0] + vertex[i].y * matRot.m[1][0] + vertex[i].z * matRot.m[2][0];
	//	rotateVertex[i].y = vertex[i].x * matRot.m[0][1] + vertex[i].y * matRot.m[1][1] + vertex[i].z * matRot.m[2][1];
	//	rotateVertex[i].z = vertex[i].x * matRot.m[0][2] + vertex[i].y * matRot.m[1][2] + vertex[i].z * matRot.m[2][2];
	//}

	#pragma endregion

	#pragma region 平行移動
	////X, Y, Z軸周りの平行移動を設定
	//worldTransform_.translation_ = {2.0f, 2.0f, 2.0f};
	////平行移動行列を宣言
	//Matrix4 matTrans = MathUtility::Matrix4Identity();

	////移動量を行列に設定する
	//matTrans.m[3][0] = worldTransform_.translation_.x;
	//matTrans.m[3][1] = worldTransform_.translation_.y;
	//matTrans.m[3][2] = worldTransform_.translation_.z;

	////単位行列を代入
	////worldTransform_.matWorld_ = MathUtility::Matrix4Identity();

	////行列の計算
	//worldTransform_.matWorld_ = TranslateMatrixCalculation(worldTransform_, matTrans);

	////行列の転送
	//worldTransform_.TransferMatrix();

	////行列の計算（Line描画）
	//for (int i = 0; i < 8; i++) {
	//	translateVertex[i].x = vertex[i].x * matTrans.m[0][0] + vertex[i].y * matTrans.m[1][0] + vertex[i].z * matTrans.m[2][0] + 1 * matTrans.m[3][0];
	//	translateVertex[i].y = vertex[i].x * matTrans.m[0][1] + vertex[i].y * matTrans.m[1][1] + vertex[i].z * matTrans.m[2][1] + 1 * matTrans.m[3][1];
	//	translateVertex[i].z = vertex[i].x * matTrans.m[0][2] + vertex[i].y * matTrans.m[1][2] + vertex[i].z * matTrans.m[2][2] + 1 * matTrans.m[3][2];
	//}

	#pragma endregion
	#pragma endregion

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 960);

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());

	//ライン描画が参照するビュープロジェクションを指定する（アドレス渡し）
	//PrimitiveDrawer::GetInstance()->SetViewProjection(&debugCamera_->GetViewProjection());

	//自キャラの生成
	player_ = new Player();
	//自キャラの初期化
	player_->Initialize(model_, textureHandle_);
}

void GameScene::Update() {

#ifdef _DEBUG
	//デバックカメラ有効
	if (input_->TriggerKey(DIK_SPACE)) {
		isDebugCameraActive != isDebugCameraActive;
	}
#endif // _DEBUG

	//デバッグカメラの更新
	if (isDebugCameraActive) {
		debugCamera_->Update();
		//viewProjection_.matView = 
	}

	//自キャラの更新
	player_->Update(player_);
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

	//自キャラの描画
	player_->Draw(viewProjection_);
	
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

//行列の拡大縮小の計算
Matrix4 MatrixCalculation(WorldTransform worldTransform_, Matrix4 matScale) {
	//値が変わらないように退避させとく
	Matrix4 holdMat = worldTransform_.matWorld_;

	for (int i = 0; i < 4; i++) {
		worldTransform_.matWorld_.m[0][i] =
		  holdMat.m[i][0] * matScale.m[0][0] + holdMat.m[i][1] * matScale.m[1][0] +
		  holdMat.m[i][2] * matScale.m[2][0] + holdMat.m[i][3] * matScale.m[3][0];
		worldTransform_.matWorld_.m[1][i] =
		  holdMat.m[i][0] * matScale.m[0][1] + holdMat.m[i][1] * matScale.m[1][1] +
		  holdMat.m[i][2] * matScale.m[2][1] + holdMat.m[i][3] * matScale.m[3][1];
		worldTransform_.matWorld_.m[i][2] =
		  holdMat.m[i][0] * matScale.m[0][2] + holdMat.m[i][1] * matScale.m[1][2] +
		  holdMat.m[i][2] * matScale.m[2][2] + holdMat.m[i][3] * matScale.m[3][2];
		worldTransform_.matWorld_.m[i][3] =
		  holdMat.m[i][0] * matScale.m[0][3] + holdMat.m[i][1] * matScale.m[1][3] +
		  holdMat.m[i][2] * matScale.m[2][3] + holdMat.m[i][3] * matScale.m[3][3];
	}

	return worldTransform_.matWorld_;
}

//行列の平行移動の計算
Matrix4 TranslateMatrixCalculation(WorldTransform worldTransform_, Matrix4 matTrans) {
	//worldTransformの4行目1、2、3列目に1を代入する
	worldTransform_.matWorld_.m[0][3] = 1.0f;
	worldTransform_.matWorld_.m[1][3] = 1.0f;
	worldTransform_.matWorld_.m[2][3] = 1.0f;

	//値が変わらないように退避させとく
	Matrix4 holdMat = worldTransform_.matWorld_;

	for (int i = 0; i < 4; i++) {
		worldTransform_.matWorld_.m[0][i] =
		  holdMat.m[i][0] * matTrans.m[0][0] + holdMat.m[i][1] * matTrans.m[1][0] +
		  holdMat.m[i][2] * matTrans.m[2][0] + holdMat.m[i][3] * matTrans.m[3][0];
		worldTransform_.matWorld_.m[1][i] =
		  holdMat.m[i][0] * matTrans.m[0][1] + holdMat.m[i][1] * matTrans.m[1][1] +
		  holdMat.m[i][2] * matTrans.m[2][1] + holdMat.m[i][3] * matTrans.m[3][1];
		worldTransform_.matWorld_.m[i][2] =
		  holdMat.m[i][0] * matTrans.m[0][2] + holdMat.m[i][1] * matTrans.m[1][2] +
		  holdMat.m[i][2] * matTrans.m[2][2] + holdMat.m[i][3] * matTrans.m[3][2];
		worldTransform_.matWorld_.m[i][3] =
		  holdMat.m[i][0] * matTrans.m[0][3] + holdMat.m[i][1] * matTrans.m[1][3] +
		  holdMat.m[i][2] * matTrans.m[2][3] + holdMat.m[i][3] * matTrans.m[3][3];
	}

	// worldTransformの4行目1、2、3列目に0を代入する
	worldTransform_.matWorld_.m[0][3] = 0.0f;
	worldTransform_.matWorld_.m[1][3] = 0.0f;
	worldTransform_.matWorld_.m[2][3] = 0.0f;

	return worldTransform_.matWorld_;
}

//行列の回転の計算(matRot1が先頭)
Matrix4 RotateMatrixCalculation(Matrix4 matRot1, Matrix4 matRot2) {
	//値が変わらないように退避させとく
	Matrix4 holdMat = matRot1;

	for (int i = 0; i < 4; i++) {
		matRot1.m[0][i] =
		  holdMat.m[i][0] * matRot2.m[0][0] + holdMat.m[i][1] * matRot2.m[1][0] +
		  holdMat.m[i][2] * matRot2.m[2][0] + holdMat.m[i][3] * matRot2.m[3][0];
		matRot1.m[1][i] =
		  holdMat.m[i][0] * matRot2.m[0][1] + holdMat.m[i][1] * matRot2.m[1][1] +
		  holdMat.m[i][2] * matRot2.m[2][1] + holdMat.m[i][3] * matRot2.m[3][1];
		matRot1.m[i][2] =
		  holdMat.m[i][0] * matRot2.m[0][2] + holdMat.m[i][1] * matRot2.m[1][2] +
		  holdMat.m[i][2] * matRot2.m[2][2] + holdMat.m[i][3] * matRot2.m[3][2];
		matRot1.m[i][3] =
		  holdMat.m[i][0] * matRot2.m[0][3] + holdMat.m[i][1] * matRot2.m[1][3] +
		  holdMat.m[i][2] * matRot2.m[2][3] + holdMat.m[i][3] * matRot2.m[3][3];
	}

	return matRot1;
}
