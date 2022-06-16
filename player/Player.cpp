#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULLポインタチェック
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

void Player::Update() {

	//プレイヤーの移動処理
	Move();
}

void Player::Draw(ViewProjection viewProjection) {

	// 3Dモデルを描画
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Player::Move() {
	//キャラクターの移動ベクトル
	Vector3 move = {0.0f, 0.0f, 0.0f};

	//キャラクターの移動速さ
	const float kPlayerSpeed = 0.2f;

	//押した方向で移動ベクトルを変更
	if (input_->PushKey(DIK_UP)) {
		move.y += kPlayerSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kPlayerSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kPlayerSpeed;
	} else if (input_->PushKey(DIK_LEFT)) {
		move.x -= kPlayerSpeed;
	}

	//キャラクター移動（ベクトルの加算）
	worldTransform_.translation_ += move;

	//移動限界座標
	const float kMoveLimiteX = 32.0f;
	const float kMoveLimiteY = 18.0f;

	//範囲を超えない処理
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimiteX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimiteX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimiteY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimiteY);

	//行列の毎フレーム処理用関数(設定、計算、転送)
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	//デバック用表示
	debugText_->SetPos(50.0f, 50.0f);
	debugText_->Printf(
	  "Root:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}