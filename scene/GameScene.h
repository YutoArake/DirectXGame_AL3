#pragma once
#include "DirectXCommon.h"
#include "Input.h"
#include "Audio.h"
#include "DebugText.h"
#include "Model.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"
#include "Sprite.h"
#include "SafeDelete.h"
#include "player/Player.h"

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

	//パーツID
	enum PartID {
		kRoot,			//大元
		kSpine,			//脊椎
		kChest,			//胸
		kHead,			//頭
		kArmL,			//左腕
		kArmR,			//右腕
		kHip,				//尻
		kLegL,			//左足
		kLegR,			//右足

		kNumPartId
	};

  private: // メンバ変数
	/// <summary>
	/// ゲームシーン用
	/// </summary>
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	///テクスチャハンドル
	uint32_t textureHandle_ = 0;

	///3Dモデル
	Model* model_ = nullptr;

	///自キャラ
	Player* player_ = nullptr;

	/// ビュープロジェクション
	ViewProjection viewProjection_;

	///デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	//カメラ上方向の角度
	float viewAngle = 0.0f;

	//デバッグカメラ有効
	bool isDebugCameraActive = false;
};
