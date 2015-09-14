#include	"iextreme.h"
#include	"BaseObj.h"
#include	"BallObj.h"

#include	"system/system.h"

Ball::Ball(const float radius, const float adjust_h,
	const Vector3& pos, const Vector3& angle,
	const Vector3& scale,
	const Vector3& color, iexMesh* insert_mesh) :BaseObjct(radius, adjust_h, pos, angle, scale, color),
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