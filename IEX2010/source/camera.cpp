#include "iextreme.h"
#include "Player.h"
#include "camera.h"

Camera::Camera() :pos(Vector3(0.0f, 10.0f, -20.0f)),angle(Vector3(0,0,0)), target(Vector3(0, 0, 0)),
cpos(Vector3(20,10,20))
{}

Camera::~Camera()
{}

void Camera::Directional()
{
	if (GetKeyState('I') < 0)cpos.y += 1.0f;
	if (GetKeyState('K') < 0)cpos.y -= 1.0f;
	if (GetKeyState('L') < 0)cpos.x += 1.0f;
	if (GetKeyState('J') < 0)cpos.x -= 1.0f;
	
	pos = target + cpos;
}

void Camera::Update()
{
	Directional();
	Set(pos, target);
}


