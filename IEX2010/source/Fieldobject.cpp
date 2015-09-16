#include "iextreme.h"
#include "Fieldobject.h"

#include "system\System.h"

Fileobject::Fileobject(const float radius, const float adjust_h,
	const Vector3& pos, const Vector3& angle,
	const Vector3& scale,
	const Vector3& color,
	const TYPE type,
	iexMesh* mesh) :BaseObjct(radius, adjust_h, pos, angle, scale, color,type),
	mesh(mesh)
{
}

Fileobject::~Fileobject()
{
	delete mesh;
}

int Fileobject::RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist)
{
	return mesh->RayPick(out, pos, vec, Dist);
}

void Fileobject::Collision(const Vector3& hit_position, BaseObjct* hit_object)
{
}

bool Fileobject::Update()
{
	mesh->SetPos(pos);
	mesh->SetScale(scale);
	mesh->SetAngle(angle);
	mesh->Update();
	return true;
}

void Fileobject::Render()
{
	//mesh->Render();
	shader->SetValue("Color", D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f));
	if(!Paint_Render(mesh))
		mesh->Render(shader,"white");
}

void Fileobject::Wave_Render()
{
	BaseObjct::Wave_Render(mesh);

}