#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULLポインタチェック
	assert(model);

	//引数のデータをメンバ変数に記録
	model_ = model;
	velocity_ = velocity;

	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("maru.png");

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() {
	//座標を移動させる(1フレーム分の移動量を足し込む)
	worldTransform_.translation_ += velocity_;

	//ワールドトランスフォームの更新
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	//時間経過でデス
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}