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
	//�f�X�t���O�̗������e���폜
	bullets_.remove_if([](std::unique_ptr<PlayerBullet>& bullet) { return bullet->IsDead(); });

	//�v���C���[�̐��񏈗�
	Rotate();
	//�v���C���[�̈ړ�����
	Move();
	//�v���C���[�̍U������
	Attack();

	//�e�X�V
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Update();
	}
}

void Player::Draw(ViewProjection viewProjection) {

	// 3D���f����`��
	model_->Draw(worldTransform_, viewProjection, textureHandle_);

	//�e�`��
	for (std::unique_ptr<PlayerBullet>& bullet : bullets_) {
		bullet->Draw(viewProjection);
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
	debugText_->SetPos(50.0f, 50.0f);
	debugText_->Printf(
	  "Player Pos:(%f,%f,%f)", worldTransform_.translation_.x, worldTransform_.translation_.y,
	  worldTransform_.translation_.z);
}

void Player::Rotate() {
	//�L�����N�^�[�̉�]����
	//�����������ňړ��x�N�g����ύX
	if (input_->PushKey(DIK_U)) {
		//���p�[�c��Y������̊p�x������
		worldTransform_.rotation_ -= {0.0f, PI / 180, 0.0f};
		if (worldTransform_.rotation_.y <= PI * (-2)) {
			worldTransform_.rotation_.y = 0.0f;
		}
	} else if (input_->PushKey(DIK_I)) {
		//���p�[�c��Y������̊p�x������
		worldTransform_.rotation_ += {0.0f, PI / 180, 0.0f};
		if (worldTransform_.rotation_.y >= PI * 2) {
			worldTransform_.rotation_.y = 0.0f;
		}
	}

	//�f�o�b�N�p�\��
	debugText_->SetPos(50.0f, 70.0f);
	debugText_->Printf(
	  "Player Rot:(%f)", worldTransform_.rotation_.y);
}

void Player::Attack() {

	if (input_->TriggerKey(DIK_A)) {
		//�e�̑��x
		const float kBulletSpeed = 1.0f;
		Vector3 velocity(0.0f, 0.0f, kBulletSpeed);

		//���x�x�N�g�������@�̌����ɍ��킹�ĉ�]������
		velocity = MatrixCalculation(velocity, worldTransform_.matWorld_);

		//�e�𐶐����A������
		std::unique_ptr<PlayerBullet> newBullet = std::make_unique<PlayerBullet>();
		newBullet->Initialize(model_, worldTransform_.translation_, velocity);

		//�e��o�^����
		bullets_.push_back(std::move(newBullet));
	}
}