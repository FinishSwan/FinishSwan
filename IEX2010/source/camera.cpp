#include "iextreme.h"
#include "Player.h"
#include "camera.h"

Camera::Camera() :pos(Vector3(0.0f, 10.0f, -20.0f)),angle(Vector3(0,0,0)), target(Vector3(0, 0, 0))
{}

Camera::~Camera()
{}

void Camera::Directional()
{
	pos=target + Vector3(20, 10, 20);
}


void Camera::Update()
{
	Directional();
	Set(pos, target);
}


