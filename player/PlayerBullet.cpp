#include "PlayerBullet.h"

void PlayerBullet::Initialize(Model* model, const Vector3& position, const Vector3& velocity) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����̃f�[�^�������o�ϐ��ɋL�^
	model_ = model;
	velocity_ = velocity;

	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("maru.png");

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	//�����Ŏ󂯎�����������W���Z�b�g
	worldTransform_.translation_ = position;
}

void PlayerBullet::Update() {
	//���W���ړ�������(1�t���[�����̈ړ��ʂ𑫂�����)
	worldTransform_.translation_ += velocity_;

	//���[���h�g�����X�t�H�[���̍X�V
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	//���Ԍo�߂Ńf�X
	if (--deathTimer_ <= 0) {
		isDead_ = true;
	}
}

void PlayerBullet::Draw(const ViewProjection& viewProjection) {

	// 3D���f����`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}