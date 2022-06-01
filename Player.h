#pragma once
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "DebugText.h"
#include "Model.h"
#include "Input.h"
#include <cassert>

class Player {
  public:
	void Initialize(Model* model, uint32_t textureHandle);

	void Update(Player* player_);

	void Move();

	void Draw(ViewProjection& viewProjection_);

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

};
