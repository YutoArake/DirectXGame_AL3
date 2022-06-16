#include "ViewProjection.h"

void ViewProjection::SetViewProjection() {
	//カメラ視点座標を設定
	eye = {0.0f, 0.0f, -50.0f};

	//カメラ注視点座標を設定
	target = {0.0f, 0.0f, 0.0f};

	//カメラ上方向ベクトルを設定(右上45度指定)
	up = {0.0f, 1.0f, 0.0f};

	//カメラ垂直方向視野角を設定
	fovAngleY = RadianTransform(45.0f);

	//アスペクト比を設定
	aspectRatio = (float)16 / 9;

	//ニアクリップ距離を設定
	nearZ = 0.1f;

	//ファークリップ距離を設定
	farZ = 1000.0f;

	//ビュープロジェクションの初期化
	Initialize();
}

void ViewProjection::UpdateViewProjention(Input* input_, DebugText* debugText_, float viewAngle) {
	//視点移動処理
	{
		//視点の移動ベクトル
		//Vector3 move = {0.0f, 0.0f, 0.0f};

		//視点の移動速さ
		//const float kEyeSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		//if (input_->PushKey(DIK_W)) {
		//	move.z += kEyeSpeed;
		//} else if (input_->PushKey(DIK_S)) {
		//	move.z -= kEyeSpeed;
		//}

		//視点移動（ベクトルの加算）
		//eye += move;

		//行列の再計算
		//UpdateMatrix();

		//デバック用表示
		//debugText_->SetPos(50.0f, 50.0f);
		//debugText_->Printf("eye:(%f,%f,%f)", eye.x, eye.y, eye.z);
	}

	//注視点移動処理
	{
		//視点の移動ベクトル
		//Vector3 move = {0.0f, 0.0f, 0.0f};

		//視点の移動速さ
		//const float kTargetSpeed = 0.2f;

		//押した方向で移動ベクトルを変更
		//if (input_->PushKey(DIK_LEFT)) {
		//	move.x -= kTargetSpeed;
		//} else if (input_->PushKey(DIK_RIGHT)) {
		//	move.x += kTargetSpeed;
		//}

		//視点移動（ベクトルの加算）
		//target += move;

		//行列の再計算
		//UpdateMatrix();

		//デバック用表示
		//debugText_->SetPos(50.0f, 70.0f);
		//debugText_->Printf("target:(%f,%f,%f)", target.x, target.y, target.z);
	}

	//上方向回転処理
	{
		//上方向の回転速さ[ラジアン/frame]
		//const float kUpRotSpeed = 0.05f;

		//押した方向で移動ベクトルを変更
		//if (input_->PushKey(DIK_SPACE)) {
		//	viewAngle += kUpRotSpeed;
		//	// 2πを超えたら0に戻す
		//	viewAngle = fmodf(viewAngle, PI * 2.0f);
		//}

		//上方向ベクトルを計算（半径1の円周上の座標）
		//up = {cosf(viewAngle), sinf(viewAngle), 0.0f};

		//行列の再計算
		//UpdateMatrix();

		//デバック用表示
		//debugText_->SetPos(50.0f, 90.0f);
		//debugText_->Printf("up:(%f,%f,%f)", up.x, up.y, up.z);
	}

	// Fov変更処理
	{
		//上キーで視野角が広がる
		//if (input_->PushKey(DIK_UP)) {
		//	fovAngleY += 0.02f;
		//	//πを超えないようにする
		//	fovAngleY = min(max(fovAngleY, 0.01f), PI);
		//	//下キーで視野角が狭まる
		//} else if (input_->PushKey(DIK_DOWN)) {
		//	fovAngleY -= 0.02f;
		//	// 0.01を下回らないようにする
		//	fovAngleY = min(max(fovAngleY, 0.01f), PI);
		//}

		//行列の再計算
		//UpdateMatrix();

		//デバック用表示
		//debugText_->SetPos(50.0f, 110.0f);
		//debugText_->Printf("fovAngleY(Degree):%f", DegreeTransform(fovAngleY));
	}

	//クリップ距離変更処理
	{
		// SHIFT,CTRLでニアクリップ距離を増減
		//if (input_->PushKey(DIK_LSHIFT)) {
		//	nearZ += 0.2f;
		//	//下キーで視野角が狭まる
		//} else if (input_->PushKey(DIK_LCONTROL)) {
		//	nearZ -= 0.2f;
		//}

		//行列の再計算
		//UpdateMatrix();

		//デバック用表示
		//debugText_->SetPos(50.0f, 130.0f);
		//debugText_->Printf("nearZ:%f", nearZ);
	}
}