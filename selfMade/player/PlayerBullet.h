#pragma once
#include "Model.h"
#include "WorldTransform.h"

#include <cassert>

/// <summary>
/// 自キャラの弾
/// </summary>
class PlayerBullet {
  public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// getter
	/// </summary>
	bool IsDead() const { return isDead_; }

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//行列
	AffinMatrix mat;

	//速度
	Vector3 velocity_;

	//寿命
	static const int32_t kLinfeTime = 60 * 5;

	//デスタイマー
	int32_t deathTimer_ = kLinfeTime;
	//デスフラグ
	bool isDead_ = false;
};
