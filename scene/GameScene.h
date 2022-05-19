﻿#pragma once

#include "Audio.h"
#include "DirectXCommon.h"
#include "DebugText.h"
#include "Input.h"
#include "Model.h"
#include "SafeDelete.h"
#include "Sprite.h"
#include "ViewProjection.h"
#include "WorldTransform.h"
#include "DebugCamera.h"

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
	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;
	DebugText* debugText_ = nullptr;

	///テクスチャハンドル
	uint32_t textureHandle_ = 0;

	///3Dモデル
	Model* model_ = nullptr;

	///ワールドトランスフォーム
	WorldTransform worldTransform_;
	/// ビュープロジェクション
	ViewProjection viewProjection_;

	///デバッグカメラ
	DebugCamera* debugCamera_ = nullptr;

	///立方体座標
	Vector3 vertex[8] = {
	  {0.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 0.0f},
      {5.0f, 0.0f, 5.0f},
      {0.0f, 0.0f, 5.0f},
	  {0.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 0.0f},
      {5.0f, 5.0f, 5.0f},
      {0.0f, 5.0f, 5.0f}
    };

	Vector3 scaleVertex[8];
	Vector3 rotateVertex[8];
	Vector3 translateVertex[8];

	//立方体の線の色
	Vector4 white = {255.0f, 255.0f, 255.0f, 1.0f};
	Vector4 red = {255.0f, 0.0f, 0.0f, 1.0f};
	Vector4 blue = {0.0f, 0.0f, 255.0f, 1.0f};
	Vector4 green = {0.0f, 255.0f, 0.0f, 1.0f};
	Vector4 black = {0.0f, 0.0f, 0.0f, 1.0f};

	//立方体の頂点の順番
	int edgeList[12][2] = {
	  {0, 1},
      {1, 2},
      {2, 3},
      {3, 0},
      {0, 4},
      {1, 5},
	  {2, 6},
      {3, 7},
      {4, 5},
      {5, 6},
      {6, 7},
      {7, 4}
	};
	/// <summary>
	/// ゲームシーン用
	/// </summary>
};
