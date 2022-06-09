#pragma once
#include "WorldTransform.h"
#include <math.h>

//円周率π
const float PI = 3.141592f;

namespace MathMyFunc {
//プロトタイプ宣言
float RadianTransform(float angle);
float DegreeTransform(float angle);

void GenerateIdentityMatrix(Matrix4& mat);
void GenerateScaleMatrix(WorldTransform worldTransform, Matrix4& matScale);
void GenerateRotateXMatrix(WorldTransform worldTransform, Matrix4& matRotate);
void GenerateRotateYMatrix(WorldTransform worldTransform, Matrix4& matRotate);
void GenerateRotateZMatrix(WorldTransform worldTransform, Matrix4& matRotate);
void GenerateTransformMatrix(WorldTransform worldTransform, Matrix4& matTrans);
Matrix4 MatrixCalculation(Matrix4 mat1, Matrix4 mat2);
//プロトタイプ宣言ここまで
} // namespace MathMyFunc
