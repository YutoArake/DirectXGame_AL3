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
	/// �s������
	/// </summary>
	void Move();

	void Approach();

	void Leave();

	//�s���t�F�[�Y
	enum class Phase {
		Approach,		//�ڋ߂���
		Leave,			//���E����
	};

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
	Vector3 approachVelocity_;
	Vector3 leaveVelocity_;

	//�t�F�[�Y
	Phase phase_ = Phase::Approach;
};