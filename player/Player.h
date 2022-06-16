#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "ViewProjection.h"
#include "Input.h"
#include "DebugText.h"
#include "MathMyFunc.h"
using namespace MathMyFunc;

#include <cassert>

/// <summary>
/// ���L����
/// </summary>
class Player {
  public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, uint32_t textureHandle);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(ViewProjection viewProjection);

	/// <summary>
	/// �ړ�����
	/// </summary>
	void Move();

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;

	//�C���v�b�g
	Input* input_ = nullptr;
	//�f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;

	//�s��
	AffinMatrix mat;

};