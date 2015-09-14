#include "iextreme.h"
#include "Player.h"
#include "camera.h"

#include "InputManager.h"

Camera::Camera() :pos(Vector3(0.0f, 10.0f, -20.0f)), angle(Vector3(0, 0, 0)), target(Vector3(0, 0, 0)), forward(Vector3(0, -1.0f, 1.0f)), length(30.0f)
{}

Camera::~Camera()
{}

void Camera::Directional()
{
	pos = target - forward * length;
}

void Camera::Rotate()
{
	Vector3 right,up;
	Vector3Cross(right, Vector3(0, 1, 0), forward);
	right.Normalize();
	Vector3Cross(up, forward,right);
	up.Normalize();

	forward += up * InputManager::GetMouseAxisY() * -0.007f;
	forward += right * InputManager::GetMouseAxisX()* 0.007f;

	//前方向の正規化
		forward.Normalize();
}

void Camera::Update()
{
	Rotate();
	//Length_Update();



	Directional();
	Set(pos, target);
}


