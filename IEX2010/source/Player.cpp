#include "iextreme.h"
#include "Player.h"
#include	"ObjectManager.h"


Player::Player(const float radius, const float adjust_h,
		const Vector3& pos, const Vector3& angle,
		const Vector3& scale,
		const Vector3& color,
		const TYPE type,
		iex3DObj* insert_skinmesh) :BaseObjct(radius,adjust_h,pos,angle,scale,color,type),
obj(insert_skinmesh)
{
}

Player::~Player()
{
	delete obj;
}

bool Player::Init(char*filename)
{
	return true;
}

void Player::Move()
{
	static float MAX_SPEED = 1;
	static float MINI_SPEED = 0.01;
 	static float ACCELATION = 0.05f;
	static float ブレーキ = 0.8f;

	//カメラの前方向
	Vector3 c_front(matView._13,0,matView._33);
	c_front.Normalize();
	//カメラの右方向
	Vector3 c_right(matView._11, 0, matView._31);
	c_right.Normalize();
	
	Vector3 temp = Vector3(0, 0, 0);
	bool is_move = false;
	if (KEY_Get(KEY_UP))
	{
		SetMotion(1);
		temp += c_front;
		is_move = true;
		//if (velocity.Length() > MAX_SPEED)
		//{
		//	velocity.Normalize();
		//	velocity *= MAX_SPEED;
		//}
	}
	
	if (KEY_Get(KEY_DOWN))
	{
		SetMotion(1);
		temp -= c_front;
		is_move = true;
		////if (velocity.Length() > MAX_SPEED)
		////{
		////	velocity.Normalize();
		////	velocity *= MAX_SPEED;
		////}
	}

	if (KEY_Get(KEY_RIGHT))
	{
		SetMotion(1);
		temp += c_right;
		is_move = true;
		//if (velocity.Length() > MAX_SPEED)
		//{
		//	velocity.Normalize();
		//	velocity *= MAX_SPEED;
		//}
	}

	if (KEY_Get(KEY_LEFT))
	{
		is_move = true;
		SetMotion(1);
		temp -= c_right;
		if (velocity.Length() > MAX_SPEED)
		{
			velocity.Normalize();
			velocity *= MAX_SPEED;
		}
	}
	temp.Normalize();
	temp *= ACCELATION;
	velocity += temp;
	if (velocity.Length() > MAX_SPEED)
	{
		velocity.Normalize();
		velocity *= MAX_SPEED;
	}

	if (!is_move)
	{
		velocity *= ブレーキ;
		if (velocity.Length() < MINI_SPEED)
		{
			velocity.Normalize();
			velocity =Vector3(0,0,0);
		}
		SetMotion(0);
	}


	
}

void Player::Rotate()
{
	if (velocity.Length() <= 0.000000001)
		return;
		Vector3 rotate = Vector3(sinf(angle.y), 0, cosf(angle.y));
		rotate.Normalize();
		Vector3 v = velocity;
		v.Normalize();

		float naiseki = Vector3Dot(rotate, v);
		naiseki = min(naiseki, 1);
		naiseki = max(naiseki, -1);

		naiseki = acos(naiseki);
		if (naiseki > 0.11f)
		{
			naiseki = 0.11f;
		}
		float gaiseki = (rotate.z*velocity.x) - (rotate.x*velocity.z);

		//if (KEY_Get(KEY_UP)){
			if (gaiseki > .0f)
			{
				angle.y += naiseki;
			}

			else{
				angle.y -= naiseki;
			}
		//}
}

void Player::SetMotion(int motion)
{
	if (obj->GetMotion() != motion)
		obj->SetMotion(motion);
}

float Player::StageWallFront ()
{
	Vector3  p_pos = pos;
	Vector3 vec, out;
	
	float dist = 10.0f;

	outZ = 0.0f;

	p_pos.x =pos.x ;
	p_pos.y +=2.0f;
	p_pos.z -=  1.0f;
	
	vec.x = 0.0f;
	vec.y = 0.0f;
	vec.z = 1.0f;

	if (obj_manager.Collision_of_RayPick(&out,&p_pos,&vec,&dist,this)!=nullptr)
	{
	 if (pos.z>out.z-2.0f)
		return out.z-2.0f;
	}
	return	pos.z;
}

float Player::StageWallBack ()
{
	Vector3  p_pos = pos;
	Vector3 vec, out;
	
	float dist = 10.0f;

	outZ = 0.0f;

	p_pos.x =pos.x ;
	p_pos.y += 2.0f;
	p_pos.z += 1.0f;
	
	vec.x = 0.0f;
	vec.y = 0.0f;
	vec.z = -1.0f;

	if (obj_manager.Collision_of_RayPick(&out,&p_pos,&vec,&dist,this)!=nullptr)
	{
	 if (pos.z<out.z+2.0f)
		return out.z+2.0f;
	}
	return	pos.z;
}

float Player::StageWallRight ()
{
	Vector3  p_pos = pos;
	Vector3 vec, out;
	
	float dist = 10.0f;

	outZ = 0.0f;

	p_pos.x -= 1.0f ;
	p_pos.y +=2.0f;
	p_pos.z =  pos.z;
	
	vec.x = 1.0f;
	vec.y = 0.0f;
	vec.z = 0.0f;

	if (obj_manager.Collision_of_RayPick(&out,&p_pos,&vec,&dist,this)!=nullptr)
	{
	 if (pos.x>out.x-2.0f)
		return out.x-2.0f;
	}
	return	pos.x;
}

float Player::StageWallLeft ()
{
	Vector3  p_pos = pos;
	Vector3 vec, out;
	
	float dist = 10.0f;

	outZ = 0.0f;

	p_pos.x +=1.0f ;
	p_pos.y +=2.0f;
	p_pos.z = pos.z;
	
	vec.x = -1.0f;
	vec.y = 0.0f;
	vec.z = 0.0f;

	if (obj_manager.Collision_of_RayPick(&out,&p_pos,&vec,&dist,this)!=nullptr)
	{
	 if (pos.x<out.x+2.0f)
		return out.x+2.0f;
	}
	return	pos.x;
}

bool Player::Update()
{
	Move();
	Rotate();
	pos += velocity;
	
	if (velocity.Length() > 0.1)
		int a = 0;

	pos.z = StageWallFront();
	pos.z = StageWallBack();
	pos.x = StageWallRight();
	pos.x = StageWallLeft();

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