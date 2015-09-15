#include	"iextreme.h"
#include	"BaseObj.h"
#include	"BallObj.h"
#include	"Wave.h"
#include	"ObjectManager.h"

#include	"system/system.h"

Ball::Ball(const float radius, const float adjust_h,
	const Vector3& pos, const Vector3& angle,
	const Vector3& scale,
	const Vector3& color,
	BaseObjct::TYPE t,
	iexMesh* insert_mesh) :BaseObjct(radius, adjust_h, pos, angle, scale, color,t),
	obj(insert_mesh), enable(false)
{
}

Ball::~Ball()
{
	delete obj;
}


bool Ball::Update()
{
	if (!enable)
		return true;
	//コリジョンチェック
	struct
	{
		Vector3 out;
		Vector3 vec;
		float dist;
		float length;
		BaseObjct* ret;
	}min,def,work;

	def.vec = move;
	def.vec.Normalize();
	def.dist = 10000.0f;
	def.out = def.vec * def.dist;


	BaseObjct::TYPE types[3] =
	{
		judge,
		floor,
		wall
	};
	for (size_t i = 0; i < 3; i++)
	{
		work = def;
		work.ret = obj_manager.Collision_of_RayPick(&work.out, &pos, &work.vec, &work.dist, this, types[i]);
		work.length = (pos - work.out).Length();
		if (i == 0 || work.length < min.length)
		{
			min = work;
		}
	}

	if (min.length < move.Length())
	{
		enable = false;
		min.ret->Paint_Start(min.out);
		if (wave->IsRender(min.ret))
		{
			wave->Reset();
		}
	}

	pos += move;
	move.y -= 9.8f/60.0f;


	obj->SetPos(pos);
	obj->SetScale(scale);
	obj->SetAngle(angle);
	obj->Update();

	return true;
}

void Ball::Render()
{
	if (!enable)
		return;

	obj->Render(shader,"black");
}

void Ball::Ball_Start(Vector3 pos, Vector3 move)
{
	this->pos = pos;
	this->move = move;
	enable = true;
}

int Ball::RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist)
{
	return obj->RayPick(out, pos, vec, Dist);
}

void Ball::Collision(const Vector3& hit_position, BaseObjct* hit_object)
{

}