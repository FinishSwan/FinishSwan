#include "Player.h"

Player::Player() :obj(NULL)
{}

Player::~Player()
{
	delete obj;
}

bool Player::Init(char*filename)
{
	obj = new iex3DObj(filename);
	return true;
}

void Player::Move(Vector3 cpos,Vector3 ctarget)
{
	//ƒJƒƒ‰•ûŒüZo
	Vector3 cangle(0, 0, 0);
	cangle = ctarget - cpos;
	cangle.y = 0;
	cangle.Normalize();


	//‘O
	if (GetKeyState('W') < 0)
	{
		pos.x += sinf(angle.y);
		pos.z += cosf(angle.y);
		SetMotion(1);
	}
	else{
		SetMotion(0);
	}
	////Œã‚ë
	//if (GetKeyState('S') < 0)
	//{
	//	pos.x -= sinf(cangle.y);
	//	pos.z -= cosf(cangle.y);
	//	SetMotion(1);
	//}

	//‰ñ“]
	if (GetKeyState('D') < 0) angle.y += 0.1f;
	if (GetKeyState('A') < 0) angle.y -= 0.1f;
}

void Player::SetMotion(int motion)
{
	if (obj->GetMotion() != motion)
		obj->SetMotion(motion);
}


bool Player::Update()
{
	//Move();
	obj->SetPos(pos);
	obj->SetScale(scale);
	obj->SetAngle(angle);
	obj->Animation();
	obj->Update();

	return true;
}

void Player::Render()
{
	obj->Render();
}