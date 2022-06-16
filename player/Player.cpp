#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	// NULL�|�C���^�`�F�b�N
	assert(model);

	//�����̃f�[�^�������o�ϐ��ɋL�^
	model_ = model;
	textureHandle_ = textureHandle;

	//�V���O���g���C���X�^���X���擾����
	input_ = Input::GetInstance();
	debugText_ = DebugText::GetInstance();

	//���[���h�ϊ��̏�����
	worldTransform_.Initialize();
}

void Player::Update() {

	//�v���C���[�̐��񏈗�
	Rotate();
	//�v���C���[�̈ړ�����
	Move();
	//�v���C���[�̍U������
	Attack();

	//�e�X�V
	if (bullet_) {
		bullet_->Update();
	}
}

void Player::Draw(ViewProjection viewProjection) {

	// 3D���f����`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	if (bullet_) {
		bullet_->Draw(viewProjection);
	}
}

void Player::Move() {
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0.0f, 0.0f, 0.0f};

	//�L�����N�^�[�̈ړ�����
	const float kPlayerSpeed = 0.2f;

	//�����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_UP)) {
		move.y += kPlayerSpeed;
	} else if (input_->PushKey(DIK_DOWN)) {
		move.y -= kPlayerSpeed;
	}
	if (input_->PushKey(DIK_RIGHT)) {
		move.x += kPlayerSpeed;
	} else if (input_->PushKey(DIK_LEFT)) {
		move.x -= kPlayerSpeed;
	}

	//�L�����N�^�[�ړ��i�x�N�g���̉��Z�j
	worldTransform_.translation_ += move;

	//�ړ����E���W
	const float kMoveLimiteX = 32.0f;
	const float kMoveLimiteY = 18.0f;

	//�͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimiteX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimiteX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimiteY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimiteY);

	//�s��̖��t���[�������p�֐�(�ݒ�A�v�Z�A�]��)
	worldTransform_.UpdateWorldTransform(worldTransform_, mat);

	//�f�o�b�N�p�\��
	debugText_->SetPos(50.0f, 70.0f);
	debugText_->Printf(
	  "Player:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}

void Player::Rotate() {
	//�L�����N�^�[�̉�]����
	//�����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_U)) {
		//���p�[�c��Y������̊p�x������
		worldTransform_.rotation_ -= {0.0f, PI / 180, 0.0f};
	} else if (input_->PushKey(DIK_I)) {
		//���p�[�c��Y������̊p�x������
		worldTransform_.rotation_ += {0.0f, PI / 180, 0.0f};
	}
}

void Player::Attack() {

	if (input_->TriggerKey(DIK_A)) {
		//�e�𐶐����A������
		PlayerBullet* newBullet = new PlayerBullet();
		newBullet->Initialize(model_, worldTransform_.translation_);

		//�e��o�^����
		bullet_ = newBullet;
	}
}