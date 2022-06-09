#include "MathMyFunc.h"
using namespace MathMyFunc;

//度数をラジアンに変換する
float MathMyFunc::RadianTransform(float angle) {
	float rad;
	rad = angle * PI / 180;
	return rad;
}

//単位行列を代入する
void MathMyFunc::GenerateIdentityMatrix(Matrix4& mat) {
	mat = {
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	};
}

void MathMyFunc::GenerateScaleMatrix(WorldTransform worldTransform, Matrix4& matScale) {
	//単位行列を代入する
	GenerateIdentityMatrix(matScale);

	//スケーリング倍率を行列に設定する
	matScale.m[0][0] = worldTransform.scale_.x;
	matScale.m[1][1] = worldTransform.scale_.y;
	matScale.m[2][2] = worldTransform.scale_.z;
}

void MathMyFunc::GenerateRotateXMatrix(WorldTransform worldTransform, Matrix4& matRotate) {
	//単位行列を代入する
	GenerateIdentityMatrix(matRotate);

	// X軸回転行列の各要素を設定する
	matRotate.m[1][1] = cos(worldTransform.rotation_.x);
	matRotate.m[1][2] = sin(worldTransform.rotation_.x);
	matRotate.m[2][1] = -sin(worldTransform.rotation_.x);
	matRotate.m[2][2] = cos(worldTransform.rotation_.x);
}

void MathMyFunc::GenerateRotateYMatrix(WorldTransform worldTransform, Matrix4& matRotate) {
	//単位行列を代入する
	GenerateIdentityMatrix(matRotate);

	// Y軸回転行列の各要素を設定する
	matRotate.m[0][0] = cos(worldTransform.rotation_.y);
	matRotate.m[0][2] = -sin(worldTransform.rotation_.y);
	matRotate.m[2][0] = sin(worldTransform.rotation_.y);
	matRotate.m[2][2] = cos(worldTransform.rotation_.y);
}

void MathMyFunc::GenerateRotateZMatrix(WorldTransform worldTransform, Matrix4& matRotate) {
	//単位行列を代入する
	GenerateIdentityMatrix(matRotate);

	// Z軸回転行列の各要素を設定する
	matRotate.m[0][0] = cos(worldTransform.rotation_.z);
	matRotate.m[0][1] = sin(worldTransform.rotation_.z);
	matRotate.m[1][0] = -sin(worldTransform.rotation_.z);
	matRotate.m[1][1] = cos(worldTransform.rotation_.z);
}

void MathMyFunc::GenerateTransformMatrix(WorldTransform worldTransform, Matrix4& matTrans) {
	//単位行列を代入する
	GenerateIdentityMatrix(matTrans);

	//移動量を行列に設定する
	matTrans.m[3][0] = worldTransform.translation_.x;
	matTrans.m[3][1] = worldTransform.translation_.y;
	matTrans.m[3][2] = worldTransform.translation_.z;
}

//行列の計算(matRot1が元になる値)
Matrix4 MathMyFunc::MatrixCalculation(Matrix4 mat1, Matrix4 mat2) {
	//値が変わらないように退避させとく
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
