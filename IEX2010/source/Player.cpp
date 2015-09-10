#include "iextreme.h"
#include "Player.h"


Player::Player(const float radius, const float adjust_h,
		const Vector3& pos, const Vector3& angle,
		const Vector3& scale,
		const Vector3& color, iex3DObj* insert_skinmesh) :BaseObjct(radius,adjust_h,pos,angle,scale,color),
obj(insert_skinmesh)
{
}

Player::~Player()
{
	delete obj;
}

bool Player::Init(char*filename)
{
	//obj = new iex3DObj(filename);
	return true;
}

void Player::Move(Vector3 cpos,Vector3 ctarget)
{
	//ƒJƒƒ‰•ûŒüZo
	Vector3 cangle= ctarget - cpos;
	cangle.y = 0;
	cangle.Normalize();
	
	float d = sqrtf(cangle.x*cangle.x + cangle.z*cangle.z);

	//‘O
	if (GetKeyState('W') < 0)
	{
		pos.x +=cangle.x;
		pos.z +=cangle.z;
		SetMotion(1);
	}
	else{
		SetMotion(0);
	}
	//Œã‚ë
	if (GetKeyState('S') < 0)
	{
		pos.x -=cangle.x;
		pos.z -=cangle.z;
		SetMotion(1);
	}
	
	//‰ñ“]
	if (GetKeyState('D') < 0)
	{
		pos.x += cangle.x*d;
		pos.z -= cangle.z*d;
	}

	if (GetKeyState('A') < 0)
	{
		pos.x -= cangle.x*d;
		pos.z += cangle.z*d;
	}
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

void Player::DebugText()
{
	char	str[64];
	wsprintf( str, "POS %03d / %03d / %03d\n", (int)pos.x, (int)pos.y,(int)pos.z );
	IEX_DrawText( str, 10,10,200,20, 0xFFFFFF00 );
}


void Player::Render()
{
	DebugText();
	obj->Render();
}

int Player::RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist)
{
	return obj->RayPick(out, pos, vec, Dist);
}

void Player::Collision(const Vector3& hit_position, BaseObjct* hit_object)
{

}