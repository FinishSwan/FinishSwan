#include "iextreme.h"
#include "Player.h"
#include	"ObjectManager.h"
#include	"Wave.h"
#include	"BallObj.h"
#include	"camera.h"
#include	"BlackCircle.h"

#include	"system/system.h"


Player::Player(const float radius, const float adjust_h,
		const Vector3& pos, const Vector3& angle,
		const Vector3& scale,
		const Vector3& color,
		const TYPE type,
		iex3DObj* insert_skinmesh) :BaseObjct(radius,adjust_h,pos,angle,scale,color,type),
		obj(insert_skinmesh), m_run_effect(new Particle_AfterImage()), NoControlTime(-1.0f), Falled(false), ball(nullptr)
{
	//ボール読み込み
	iexMesh* insert_ball = new iexMesh("DATA\\IMO\\Ball.IMO");


	ball = new Ball(1,
		0.3,
		Vector3(0, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0.05f, 0.05f, 0.05f),
		Vector3(1, 1, 1), BaseObjct::TYPE::judge,
		insert_ball);
}

Player::~Player()
{
    delete m_run_effect;
	delete obj;
	delete ball;
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
	if (KEY_Get(KEY_UP) && IsCanControl())
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
	
	if (KEY_Get(KEY_DOWN) && IsCanControl())
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

	if (KEY_Get(KEY_RIGHT) && IsCanControl())
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

	if (KEY_Get(KEY_LEFT) && IsCanControl())
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

		/*if (KEY_Get(KEY_UP)){*/
		if (IsCanControl())
		{
			if (gaiseki > .0f)
			{
				angle.y += naiseki;
			}

			else{
				angle.y -= naiseki;
			}

		}
		
}

void Player::SetMotion(int motion)
{
	if (!IsCanControl())
		return;
	if (obj->GetMotion() != motion)
		obj->SetMotion(motion);
}

float Player::StageWallFront(Vector3* ptr_vec)
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
		*ptr_vec = vec;
	 if (pos.z>out.z-2.0f)
		return out.z-2.0f;
	}
	return	pos.z;
}

float Player::StageWallBack(Vector3* ptr_vec)
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
		*ptr_vec = vec;
	 if (pos.z<out.z+2.0f)
		return out.z+2.0f;
	}
	return	pos.z;
}

float Player::StageWallRight(Vector3* ptr_vec)
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
		*ptr_vec = vec;
	 if (pos.x>out.x-2.0f)
		return out.x-2.0f;
	}
	return	pos.x;
}

float Player::StageWallLeft(Vector3* ptr_vec)
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
		*ptr_vec = vec;
	 if (pos.x<out.x+2.0f)
		return out.x+2.0f;
	}
	return	pos.x;
}

bool Player::Update()
{
	NoControlTime -= 1.0f / 60.0f;

	if (blackcircle->IsBlacked() && IsCanControl())
	{
		Fall();
	}

	if (Falled)
	{
		FallSpeed += 0.06f;
		pos.y -= FallSpeed;
	}
	Vector3 BeforePos = pos;
	Move();
	Rotate();
	pos += velocity;
	
	if (velocity.Length() > 0.1)
		int a = 0;
	
	Vector3 normal = Vector3(0,0,0);

	if (!Falled)
	{ 
		pos.z = StageWallFront(&normal);
		pos.z = StageWallBack(&normal);
		pos.x = StageWallRight(&normal);
		pos.x = StageWallLeft(&normal);
	}
	if (normal.Length() > 0.9f && velocity.Length() > 0.01f)
	{
		normal.y = .0f;
		normal.Normalize();
		//normal.y = 0.5f;
		//normal.Normalize();
		Vector3 len = pos - BeforePos;
		len.Normalize();
		float dot = Vector3Dot(velocity, len);
		float power = Vector3Dot(velocity, -normal);
		velocity.Normalize();
		velocity *= dot;
		wave->Start_Wave(pos + Vector3(0, 2, 0), -normal, 5.0f + 6.0f * power, (5.0f + 6.0f * power) * 15.0f);
	}
    
	//投球
	if (KEY_Get(KEY_SPACE) == 3 && IsCanControl())
		Throw_Start();



    Vector3 effect_pos = pos;
    effect_pos.y += 8.8f;
    m_run_effect->Execute(effect_pos, velocity);

	obj->SetPos(pos);
	obj->SetScale(scale);
	obj->SetAngle(angle);
	obj->Animation();
	obj->Update();

	if (IsBallThrow())
	{
		Matrix mat;
		Vector3 front = Vector3(sinf(angle.y), 0, cosf(angle.y));
		mat = *obj->GetBone(7);
		//mat._41 += mat._13 * 20.0f;
		//mat._42 += mat._23 * 20.0f;
		//mat._43 += mat._33 * 20.0f;
		mat *= obj->TransMatrix;
		ball->Ball_Start(Vector3(mat._41, mat._42, mat._43), front * 3.0f);
		obj->SetParam(0, 0);
	}
	ball->Update();
	return true;
}

void Player::Throw_Start()
{
	obj->SetMotion(7);
	Vector3 forward = camera->GetForward();
	forward.y = .0f;
	forward.Normalize();
	angle.y = atan2f(forward.x, forward.z);
	NoControlTime = 3.0f;
}

void Player::DebugText()
{
	char	str[64];
	wsprintf( str, "POS %03d / %03d / %03d\n", (int)pos.x, (int)pos.y,(int)pos.z );
	IEX_DrawText( str, 10,10,200,20, 0xFFFFFF00 );
}


void Player::Render()
{
	//obj->Render();
	//DebugText();
	shader->SetValue("Color", D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f));
	if (!Paint_Render(obj))
		obj->Render(shader,"color");

	ball->Render();
}

int Player::RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist)
{
	return obj->RayPick(out, pos, vec, Dist);
}

void Player::Collision(const Vector3& hit_position, BaseObjct* hit_object)
{

}
void Player::Wave_Render()
{
	BaseObjct::Wave_Render(obj);

}
void Player::Fall()
{
	Falled = true;
	FallSpeed = .0f;
	obj->SetMotion(6);
	NoControlTime = 20.0f;
}