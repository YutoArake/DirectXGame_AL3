#include "WorldTransform.h"

void WorldTransform::UpdateWorldTransform(WorldTransform &worldTransform, AffinMatrix mat) {
	//各種行列設定
	GenerateScaleMatrix(worldTransform.scale_, mat.scale);
	GenerateRotateXMatrix(worldTransform.rotation_, mat.rotX);
	GenerateRotateYMatrix(worldTransform.rotation_, mat.rotY);
	GenerateRotateZMatrix(worldTransform.rotation_, mat.rotZ);
	GenerateTransformMatrix(worldTransform.translation_, mat.trans);

	//回転行列の合成
	mat.rot = MatrixCalculation(MatrixCalculation(mat.rotX, mat.rotZ), mat.rotY);

	//行列の合成
	mat.mix = MatrixCalculation(MatrixCalculation(mat.scale, mat.rot), mat.trans);

	//行列の計算
	//単位行列代入
	GenerateIdentityMatrix(worldTransform.matWorld_);
	//スケール、回転、平行移動行列の計算
	worldTransform.matWorld_ = MatrixCalculation(worldTransform.matWorld_, mat.mix);
	//親のワールド行列と計算
	if (worldTransform.parent_ != NULL) {
		worldTransform.matWorld_ =
		  MatrixCalculation(worldTransform.matWorld_, worldTransform.parent_->matWorld_);
	}

	//行列の転送
	worldTransform.TransferMatrix();
}