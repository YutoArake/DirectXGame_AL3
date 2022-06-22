#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "DebugText.h"

#include <cassert>

/// <summary>
/// 敵
/// </summary>
class Enemy {
  public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//デバックテキスト
	DebugText* debugText_ = nullptr;

	//行列
	AffinMatrix mat;

	//速度
	Vector3 velocity_;
};