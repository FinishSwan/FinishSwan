#include "iextreme.h"
#include "Player.h"
#include "camera.h"

#include "ObjectManager.h"
#include "InputManager.h"


/**
*@brief 線形補間
*@param[1] 始点
*@param[2] 終点
*@param[3] 始点から終点までの補間率
*/
float liner_hokan(const float start, const float end, float t)
{

	return start + (end - start) * t;
}


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
	Vector3 temp = forward+ up* InputManager::GetMouseAxisY() * -0.007f;
	temp.Normalize();
	Vector3 kizyun(0, 1, 0);
	float naiseki = Vector3Dot(kizyun, temp);
	naiseki = max(-1, naiseki);
	naiseki = min(1, naiseki);
	naiseki = acos(naiseki);
	
	move = Vector3(0, 0, 0);
	if ((naiseki > 1.0) && ( naiseki < 2.8))
	{
		forward += up* InputManager::GetMouseAxisY() * -0.007f;
		move += up* InputManager::GetMouseAxisY() * -0.007f;
	}
		forward += right * InputManager::GetMouseAxisX()* 0.007f;
	move +=right * InputManager::GetMouseAxisX()* 0.007f;
	
	//前方向の正規化
	forward.Normalize();
}

void Camera::Calculate_Length()
{
	Vector3 back = -forward;
	back.Normalize();

	float dist = 15.0f;
	Vector3 out;
	Vector3 s_pos = pos;
	s_pos -= back *5.0f;

	if (obj_manager.Collision_of_RayPick(&out, &s_pos, &back, &dist,nullptr,BaseObjct::judge))
	{
		Vector3 vec = target - out;
		float kyori = vec.Length();
		if (length > kyori)
		{
			length = kyori;
		}
	}
	else
	{
		length = 30;
	}
}


void Camera::Update()
{
	Rotate();
	Calculate_Length();
	//Length_Update();
	Directional();

	Set(pos, target);
}




