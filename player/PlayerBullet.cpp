#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position) {
	// NULLポインタチェック
	assert(model);

	//引数のデータをメンバ変数に記録
	model_ = model;
	//テクスチャ読み込み
	textureHandle_ = TextureManager::Load("maru.png");

	//ワールドトランスフォームの初期化
	worldTransform_.Initialize();
	//引数で受け取った初期座標をセット
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() {
	//ワールドトランスフォームの更新
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}