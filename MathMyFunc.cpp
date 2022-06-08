#include "MathMyFunc.h"
using namespace MathMyFunc;

//�x�������W�A���ɕϊ�����
float MathMyFunc::RadianTransform(float angle) {
	float rad;
	rad = angle * PI / 180;
	return rad;
}

//�P�ʍs���������
void MathMyFunc::GenerateIdentityMatrix(Matrix4& mat) {
	mat = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	       0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
}

void MathMyFunc::GenerateScaleMatrix(WorldTransform worldTransform, Matrix4& matScale) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matScale);

	//�X�P�[�����O�{�����s��ɐݒ肷��
	matScale.m[0][0] = worldTransform.scale_.x;
	matScale.m[1][1] = worldTransform.scale_.y;
	matScale.m[2][2] = worldTransform.scale_.z;
}

void MathMyFunc::GenerateRotateXMatrix(WorldTransform worldTransform, Matrix4& matRotate) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matRotate);

	// X����]�s��̊e�v�f��ݒ肷��
	matRotate.m[1][1] = cos(worldTransform.rotation_.x);
	matRotate.m[1][2] = sin(worldTransform.rotation_.x);
	matRotate.m[2][1] = -sin(worldTransform.rotation_.x);
	matRotate.m[2][2] = cos(worldTransform.rotation_.x);
}

void MathMyFunc::GenerateRotateYMatrix(WorldTransform worldTransform, Matrix4& matRotate) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matRotate);

	// Y����]�s��̊e�v�f��ݒ肷��
	matRotate.m[0][0] = cos(worldTransform.rotation_.y);
	matRotate.m[0][2] = -sin(worldTransform.rotation_.y);
	matRotate.m[2][0] = sin(worldTransform.rotation_.y);
	matRotate.m[2][2] = cos(worldTransform.rotation_.y);
}

void MathMyFunc::GenerateRotateZMatrix(WorldTransform worldTransform, Matrix4& matRotate) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matRotate);

	// Z����]�s��̊e�v�f��ݒ肷��
	matRotate.m[0][0] = cos(worldTransform.rotation_.z);
	matRotate.m[0][1] = sin(worldTransform.rotation_.z);
	matRotate.m[1][0] = -sin(worldTransform.rotation_.z);
	matRotate.m[1][1] = cos(worldTransform.rotation_.z);
}

void MathMyFunc::GenerateTransformMatrix(WorldTransform worldTransform, Matrix4& matTrans) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matTrans);

	//�ړ��ʂ��s��ɐݒ肷��
	matTrans.m[3][0] = worldTransform.translation_.x;
	matTrans.m[3][1] = worldTransform.translation_.y;
	matTrans.m[3][2] = worldTransform.translation_.z;
}

//�s��̌v�Z(matRot1�����ɂȂ�l)
Matrix4 MathMyFunc::MatrixCalculation(Matrix4 matRot1, Matrix4 matRot2) {
	//�l���ς��Ȃ��悤�ɑޔ������Ƃ�
	Matrix4 holdMat = matRot1;

	for (int i = 0; i < 4; i++) {
		matRot1.m[0][i] = holdMat.m[0][0] * matRot2.m[0][i] + holdMat.m[0][1] * matRot2.m[1][i] +
		                  holdMat.m[0][2] * matRot2.m[2][i] + holdMat.m[0][3] * matRot2.m[3][i];
		matRot1.m[1][i] = holdMat.m[1][0] * matRot2.m[0][i] + holdMat.m[1][1] * matRot2.m[1][i] +
		                  holdMat.m[1][2] * matRot2.m[2][i] + holdMat.m[1][3] * matRot2.m[3][i];
		matRot1.m[2][i] = holdMat.m[2][0] * matRot2.m[0][i] + holdMat.m[2][1] * matRot2.m[1][i] +
		                  holdMat.m[2][2] * matRot2.m[2][i] + holdMat.m[2][3] * matRot2.m[3][i];
		matRot1.m[3][i] = holdMat.m[3][0] * matRot2.m[0][i] + holdMat.m[3][1] * matRot2.m[1][i] +
		                  holdMat.m[3][2] * matRot2.m[2][i] + holdMat.m[3][3] * matRot2.m[3][i];
	}

	return matRot1;
}
