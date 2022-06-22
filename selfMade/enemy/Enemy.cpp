#include "Enemy.h"

void Enemy::Initialize(Model* model) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����̃f�[�^�������o�ϐ��ɋL�^
	model_ = model;

	//������
	velocity_ = {0.0f, 0.0f, -0.2f};
	approachVelocity_ = {0.0f, 0.0f, -0.2f};
	leaveVelocity_ = {-0.2f, 0.2f, -0.2f};

	//�e�N�X�`���ǂݍ���
	textureHandle_ = TextureManager::Load("youkai_backbeard.png");

	//�V���O���g���C���X�^���X���擾����
	debugText_ = DebugText::GetInstance();

	//���[���h�g�����X�t�H�[���̏�����
	worldTransform_.Initialize();
	worldTransform_.translation_ = {0.0f, 2.0f, 10.0f};
}

void Enemy::Update() {

	//�s��
	switch (phase_) {
	case Phase::Approach:
		//�ڋ�
		Approach();
		break;
	case Phase::Leave:
		//���E
		Leave();
		break;
	default:
		break;
	}

	//���[���h�g�����X�t�H�[���̍X�V
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	//�f�o�b�N�p�\��
	debugText_->SetPos(50.0f, 90.0f);
	debugText_->Printf(
	  "Enemy Pos:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}

void Enemy::Draw(const ViewProjection& viewProjection) {

	// 3D���f����`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);
}

void Enemy::Move() {
	//���[���h���W�ɑ��x�𑫂�
	worldTransform_.translation_ += velocity_;
}

void Enemy::Approach() {

	//�ړ�(�x�N�g�������Z)
	worldTransform_.translation_ += approachVelocity_;

	//�K��̈ʒu�ɓ��B�����痣�E
	if (worldTransform_.translation_.z < 0.0f) {
		phase_ = Phase::Leave;
	}
}

void Enemy::Leave() {
	//�ړ�(�x�N�g�������Z)
	worldTransform_.translation_ += leaveVelocity_;
}