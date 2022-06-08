#include "GameScene.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include <cassert>
#include <math.h>

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

	//デバッグカメラの生成
	debugCamera_ = new DebugCamera(1280, 960);

#pragma region アフィン変換

#pragma region 拡縮
	// X, Y, Z方向のスケーリングを設定
	worldTransform_.scale_ = {5.0f, 5.0f, 5.0f};

	//スケーリング行列を宣言
	Matrix4 matScale;

	//スケーリング倍率を行列に設定する
	GenerateScaleMatrix(worldTransform_, matScale);

#pragma endregion

#pragma region 回転
	//X, Y, Z軸周りの回転角を設定
	worldTransform_.rotation_ = {RadianTransform(45.0f), RadianTransform(45.0f), 0.0f};

	//合成用回転行列を宣言
	 Matrix4 matRot;

	//各軸用回転行列を宣言
	 Matrix4 matRotX, matRotY, matRotZ;

	 // X, Y, Z軸回転行列の各要素を設定する
	 GenerateRotateXMatrix(worldTransform_, matRotX);
	 GenerateRotateYMatrix(worldTransform_, matRotY);
	 GenerateRotateZMatrix(worldTransform_, matRotZ);
	
	//各軸の回転行列を合成
	 matRot = MatrixCalculation(MatrixCalculation(matRotZ, matRotX), matRotY);

#pragma endregion

#pragma region 平行移動
	//X, Y, Z軸周りの平行移動を設定
	 worldTransform_.translation_ = {10.0f, 10.0f, 10.0f};
	//平行移動行列を宣言
	 Matrix4 matTrans;

	//移動量を行列に設定する
	GenerateTransformMatrix(worldTransform_, matTrans);

#pragma endregion
	 //単位行列を代入
	 GenerateIdentityMatrix(worldTransform_.matWorld_);

	 //行列の合成(scale * rot * transの順番)
	 worldTransform_.matWorld_ = MatrixCalculation(worldTransform_.matWorld_, matScale);
	 worldTransform_.matWorld_ = MatrixCalculation(worldTransform_.matWorld_, matRot);
	 worldTransform_.matWorld_ = MatrixCalculation(worldTransform_.matWorld_, matTrans);
	 
	//行列の転送
	 worldTransform_.TransferMatrix();

#pragma endregion

	//軸方向表示の表示を有効にする
	AxisIndicator::GetInstance()->SetVisible(true);
	//軸方向表示が参照するビュープロジェクションを指定する（アドレス渡し）
	AxisIndicator::GetInstance()->SetTargetViewProjection(&debugCamera_->GetViewProjection());
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