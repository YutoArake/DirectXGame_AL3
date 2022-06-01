#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULLポインタチェック
	assert(model);

	//引数のデータをメンバ変数に記録
	model_ = model;
	textureHandle_ = textureHandle;

	//シングルトンインスタンスを取得する
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//ワールド変換の初期化
	worldTransform_.Initialize();
}

void Player::Update(Player* player_) {

	//自キャラの移動
	player_->Move();

	//デバッグテキストの処理(自機の位置を表示)
	debugText_->Printf(
	  "X = %f Y = %f Z = %f", worldTransform_.translation_.x,
	  worldTransform_.translation_.y, worldTransform_.translation_.z);
}

void Player::Move() {
	//キャラクターの移動ベクトル
	Vector3 move = {0, 0, 0};

	//移動ベクトルを変更する処理
	if (input_->PushKey(DIK_W )) {
		move.y += 0.2f;
	}
	if (input_->PushKey(DIK_S)) {
		move.y -= 0.2f;
	}
	if (input_->PushKey(DIK_A)) {
		move.x -= 0.2f;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += 0.2f;
	}

	//座標移動(ベクトル加算)
	worldTransform_.translation_ += move;

	//移動限界座標
	const float kMoveLimiteX = 32.0f;
	const float kMoveLimiteY = 18.0f;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimiteX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimiteX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimiteY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimiteY);

	//行列の更新
	worldTransform_.matWorld_ = {
	  1, 0, 0, 0,
	  0, 1, 0, 0,
	  0, 0, 1, 0,
	  worldTransform_.translation_.x,
	  worldTransform_.translation_.y,
	  worldTransform_.translation_.z,
	  1
	};

	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection_) {
	//3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

}
