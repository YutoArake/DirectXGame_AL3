#include "Enemy.h"

void Enemy::Initialize(Model* model) {
	// NULLポインタチェック
	assert(model);

	//引数のデータをメンバ変数に記録
	model_ = model;

	//初期化
	velocity_ = {0.0f, 0.0f, -0.2f};

	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("youkai_backbeard.png");

	//シングルトンインスタンスを取得する
	debugText_ = DebugText::GetInstance();

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 2.0f, 10.0f};
}

void Enemy::Update() {
	//移動処理
	Move();

	//ワールドトランスフォームの更新
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Move() {
	//ワールド座標に速度を足す
	worldTransform_.translation_ += velocity_;

	//デバック用表示
	debugText_->SetPos(50.0f, 90.0f);
	debugText_->Printf(
	  "Enemy Pos:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}