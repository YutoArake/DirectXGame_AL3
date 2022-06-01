#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "DebugCamera.h"
#include "Player.h"
#include "AxisIndicator.h"
#include "TextureManager.h"
#include "PrimitiveDrawer.h"
#include <cassert>
#include <math.h>

//円周率π
const float PI = 3.141592f;

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene {

  public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

  private: // メンバ変数
	Audio* audio_ = nullptr;
	DirectXCommon* dxCommon_ = nullptr;
	DebugText* debugText_ = nullptr;
	Input* input_ = nullptr;

	///テクスチャハンドル
	uint32_t textureHandle_ = 0;

	///3Dモデル
	Model* model_ = nullptr;

	/// ビュープロジェクション
	ViewProjection viewProjection_;

	///デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;
	//デバックカメラ有効
	bool isDebugCameraActive = false;

	//自キャラ
	Player* player_ = nullptr;
	
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
