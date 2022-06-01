#include "Player.h"

void Player::Initialize(Model* model, uint32_t textureHandle) {
	//NULL�|�C���^�`�F�b�N
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

void Player::Update(Player* player_) {

	//���L�����̈ړ�
	player_->Move();

	//�f�o�b�O�e�L�X�g�̏���(���@�̈ʒu��\��)
	debugText_->Printf(
	  "X = %f Y = %f Z = %f", worldTransform_.translation_.x,
	  worldTransform_.translation_.y, worldTransform_.translation_.z);
}

void Player::Move() {
	//�L�����N�^�[�̈ړ��x�N�g��
	Vector3 move = {0, 0, 0};

	//�ړ��x�N�g����ύX���鏈��
	if (input_->PushKey(DIK_W )) {
		move.y += 0.2f;
	}
	if (input_->PushKey(DIK_S)) {
		move.y -= 0.2f;
	}
	if (input_->PushKey(DIK_A)) {
		move.x -= 0.2f;
	}
	if (input_->PushKey(DIK_D)) {
		move.x += 0.2f;
	}

	//���W�ړ�(�x�N�g�����Z)
	worldTransform_.translation_ += move;

	//�ړ����E���W
	const float kMoveLimiteX = 32.0f;
	const float kMoveLimiteY = 18.0f;

	//�͈͂𒴂��Ȃ�����
	worldTransform_.translation_.x = max(worldTransform_.translation_.x, -kMoveLimiteX);
	worldTransform_.translation_.x = min(worldTransform_.translation_.x, +kMoveLimiteX);
	worldTransform_.translation_.y = max(worldTransform_.translation_.y, -kMoveLimiteY);
	worldTransform_.translation_.y = min(worldTransform_.translation_.y, +kMoveLimiteY);

	//�s��̍X�V
	worldTransform_.matWorld_ = {
	  1, 0, 0, 0,
	  0, 1, 0, 0,
	  0, 0, 1, 0,
	  worldTransform_.translation_.x,
	  worldTransform_.translation_.y,
	  worldTransform_.translation_.z,
	  1
	};

	worldTransform_.TransferMatrix();
}

void Player::Draw(ViewProjection& viewProjection_) {
	//3D���f����`��
	model_->Draw(worldTransform_, viewProjection_, textureHandle_);

}
