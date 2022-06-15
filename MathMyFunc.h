#pragma once
#include "Vector3.h"
#include "Matrix4.h"
#include <math.h>

//円周率π
const float PI = 3.141592f;

//構造体
typedef struct {
	Matrix4 mix;
	Matrix4 scale;
	Matrix4 rotX;
	Matrix4 rotY;
	Matrix4 rotZ;
	Matrix4 rot;
	Matrix4 trans;
} AffinMatrix;

namespace MathMyFunc {

//プロトタイプ宣言
float RadianTransform(float angle);
float DegreeTransform(float angle);

void GenerateIdentityMatrix(Matrix4& mat);
void GenerateScaleMatrix(Vector3 scale, Matrix4& matScale);
void GenerateRotateXMatrix(Vector3 rotation, Matrix4& matRotation);
void GenerateRotateYMatrix(Vector3 rotation, Matrix4& matRotation);
void GenerateRotateZMatrix(Vector3 rotation, Matrix4& matRotation);
void GenerateTransformMatrix(Vector3 translation, Matrix4& matTrans);
Matrix4 MatrixCalculation(Matrix4 mat1, Matrix4 mat2);
//プロトタイプ宣言ここまで

} // namespace MathMyFunc