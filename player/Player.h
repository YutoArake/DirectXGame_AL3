#pragma once
#include "ViewProjection.h"
#include "Input.h"
#include "DebugText.h"
#include "player/PlayerBullet.h"
#include <memory>
#include <list>

/// <summary>
/// 自キャラ
/// </summary>
class Player {
  public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// 更新
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// 移動処理
	/// </summary>
	void Move();

	/// <summary>
	/// 旋回処理
	/// </summary>
	void Rotate();

	/// <summary>
	/// 攻撃
	/// </summary>
	void Attack();

  private:
	//ワールド変換データ
	WorldTransform worldTransform_;
	//モデル
	Model* model_ = nullptr;
	//テクスチャハンドル
	uint32_t textureHandle_ = 0;

	//インプット
	Input* input_ = nullptr;
	//デバックテキスト
	DebugText* debugText_ = nullptr;

	//行列
	AffinMatrix mat;

	//弾
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};