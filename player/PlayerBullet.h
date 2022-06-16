#pragma once
#include "Model.h"
#include "WorldTransform.h"
#include "Vector3.h"
#include "MathMyFunc.h"
using namespace MathMyFunc;

#include <cassert>

/// <summary>
/// ���L�����̒e
/// </summary>
class PlayerBullet {
  public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, const Vector3& position);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;

	//�s��
	AffinMatrix mat;
};
