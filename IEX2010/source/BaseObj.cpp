#include	"iextreme.h"
#include	"BaseObj.h"

#include	"system\System.h"

BaseObjct::BaseObjct(const float radius, const float adjust_h,
		const Vector3& pos, 
		const Vector3& angle,
		const Vector3& scale,
		const Vector3& color,
		const TYPE type) :
		pos(pos), scale(scale), angle(angle),
		color(color), type(type), radius(radius), adjust_height(adjust_h), velocity(Vector3(0, 0, 0)), Painted(false)
		
{

}

BaseObjct::~BaseObjct()
{
	
}

void	BaseObjct::Paint_Start(Vector3 pos)
{
	PaintPos = pos;
	PaintRange = .0f;
	Painted = true;
}


bool	BaseObjct::Base_Update()
{
	Paint_Update();
	return Update();
}

void	BaseObjct::Paint_Update()
{
	PaintRange += 0.1f;
}

bool	BaseObjct::Paint_Render(iexMesh* mesh)
{
	if (!Painted)
		return false;
	shader->SetValue("PaintPos", PaintPos);
	shader->SetValue("PaintRange", PaintRange);

	mesh->Render(shader, "paint");

	return true;
}

void	BaseObjct::Wave_Render(iexMesh* mesh)
{
	mesh->Render(shader, "wave");

	return;
}

bool  BaseObjct::IsPainted()
{
	return Painted;
}