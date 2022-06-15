#include "MathMyFunc.h"
using namespace MathMyFunc;

//�x�������W�A���ɕϊ�����
float MathMyFunc::RadianTransform(float angle) {
	float rad;
	rad = angle * PI / 180;
	return rad;
}

float MathMyFunc::DegreeTransform(float angle) {
	float degree;
	degree = angle * 180 / PI;
	return degree;
}

//�P�ʍs���������
void MathMyFunc::GenerateIdentityMatrix(Matrix4& mat) {
	mat = {1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f,
	       0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f};
}

void MathMyFunc::GenerateScaleMatrix(Vector3 scale, Matrix4& matScale) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matScale);

	//�X�P�[�����O�{�����s��ɐݒ肷��
	matScale.m[0][0] = scale.x;
	matScale.m[1][1] = scale.y;
	matScale.m[2][2] = scale.z;
}

void MathMyFunc::GenerateRotateXMatrix(Vector3 rotation, Matrix4& matRotation) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matRotation);

	// X����]�s��̊e�v�f��ݒ肷��
	matRotation.m[1][1] = cos(rotation.x);
	matRotation.m[1][2] = sin(rotation.x);
	matRotation.m[2][1] = -sin(rotation.x);
	matRotation.m[2][2] = cos(rotation.x);
}

void MathMyFunc::GenerateRotateYMatrix(Vector3 rotation, Matrix4& matRotation) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matRotation);

	// Y����]�s��̊e�v�f��ݒ肷��
	matRotation.m[0][0] = cos(rotation.y);
	matRotation.m[0][2] = -sin(rotation.y);
	matRotation.m[2][0] = sin(rotation.y);
	matRotation.m[2][2] = cos(rotation.y);
}

void MathMyFunc::GenerateRotateZMatrix(Vector3 rotation, Matrix4& matRotation) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matRotation);

	// Z����]�s��̊e�v�f��ݒ肷��
	matRotation.m[0][0] = cos(rotation.z);
	matRotation.m[0][1] = sin(rotation.z);
	matRotation.m[1][0] = -sin(rotation.z);
	matRotation.m[1][1] = cos(rotation.z);
}

void MathMyFunc::GenerateTransformMatrix(Vector3 translation, Matrix4& matTrans) {
	//�P�ʍs���������
	GenerateIdentityMatrix(matTrans);

	//�ړ��ʂ��s��ɐݒ肷��
	matTrans.m[3][0] = translation.x;
	matTrans.m[3][1] = translation.y;
	matTrans.m[3][2] = translation.z;
}

//�s��̌v�Z(mat1�����ɂȂ�l)
Matrix4 MathMyFunc::MatrixCalculation(Matrix4 mat1, Matrix4 mat2) {
	//�l���ς��Ȃ��悤�ɑޔ������Ƃ�
	Matrix4 holdMat = mat1;

	for (int i = 0; i < 4; i++) {
		mat1.m[0][i] = holdMat.m[0][0] * mat2.m[0][i] + holdMat.m[0][1] * mat2.m[1][i] +
		               holdMat.m[0][2] * mat2.m[2][i] + holdMat.m[0][3] * mat2.m[3][i];
		mat1.m[1][i] = holdMat.m[1][0] * mat2.m[0][i] + holdMat.m[1][1] * mat2.m[1][i] +
		               holdMat.m[1][2] * mat2.m[2][i] + holdMat.m[1][3] * mat2.m[3][i];
		mat1.m[2][i] = holdMat.m[2][0] * mat2.m[0][i] + holdMat.m[2][1] * mat2.m[1][i] +
		               holdMat.m[2][2] * mat2.m[2][i] + holdMat.m[2][3] * mat2.m[3][i];
		mat1.m[3][i] = holdMat.m[3][0] * mat2.m[0][i] + holdMat.m[3][1] * mat2.m[1][i] +
		               holdMat.m[3][2] * mat2.m[2][i] + holdMat.m[3][3] * mat2.m[3][i];
	}

	return mat1;
}
