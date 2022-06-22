#pragma once
#include "Model.h"
#include "WorldTransform.h"

#include <cassert>

/// <summary>
/// ���L�����̒e
/// </summary>
class PlayerBullet {
  public:
	/// <summary>
	/// ������
	/// </summary>
	void Initialize(Model* model, const Vector3& position, const Vector3& velocity);

	/// <summary>
	/// �X�V
	/// </summary>
	void Update();

	/// <summary>
	/// �`��
	/// </summary>
	void Draw(const ViewProjection& viewProjection);

	/// <summary>
	/// getter
	/// </summary>
	bool IsDead() const { return isDead_; }

  private:
	//���[���h�ϊ��f�[�^
	WorldTransform worldTransform_;
	//���f��
	Model* model_ = nullptr;
	//�e�N�X�`���n���h��
	uint32_t textureHandle_ = 0;

	//�s��
	AffinMatrix mat;

	//���x
	Vector3 velocity_;

	//����
	static const int32_t kLinfeTime = 60 * 5;

	//�f�X�^�C�}�[
	int32_t deathTimer_ = kLinfeTime;
	//�f�X�t���O
	bool isDead_ = false;
};
