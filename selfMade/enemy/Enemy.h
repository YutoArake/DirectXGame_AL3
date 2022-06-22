#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "DebugText.h"

#include <cassert>

/// <summary>
/// �G
/// </summary>
class Enemy {
  public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

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

	//�f�o�b�N�e�L�X�g
	DebugText* debugText_ = nullptr;

	//�s��
	AffinMatrix mat;

	//���x
	Vector3 velocity_;
};