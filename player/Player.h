#pragma once
#include "ViewProjection.h"
#include "Input.h"
#include "DebugText.h"
#include "player/PlayerBullet.h"
#include <memory>
#include <list>

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

	/// <summary>
	/// ���񏈗�
	/// </summary>
	void Rotate();

	/// <summary>
	/// �U��
	/// </summary>
	void Attack();

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

	//�e
	std::list<std::unique_ptr<PlayerBullet>> bullets_;
};