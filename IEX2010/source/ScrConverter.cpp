#include "iextreme.h"
#include "ScrConverter.h"

Vector3  ScrConverter::Convert_ToCliantPos_FromScrPos(Vector3 Scr)
{
	Scr.x = Scr.x * (iexSystem::ScreenWidth / 2) + (iexSystem::ScreenWidth / 2);
	Scr.y = -Scr.y * (iexSystem::ScreenHeight / 2) + (iexSystem::ScreenHeight / 2);
	return Scr;
}

Vector3  ScrConverter::Convert_ToWorldPos_FromScrPos(Vector3 Scr)
{
	D3DXMATRIX  mat;
	Vector3 temp;

	D3DXMatrixIdentity(&mat);
	D3DXMatrixInverse(&mat, NULL, &matProjection);

	temp.x = Scr.x* mat._11 + Scr.y*mat._21 + Scr.z*mat._31 + 1.0f*mat._41;
	temp.y = Scr.x* mat._12 + Scr.y*mat._22 + Scr.z*mat._32 + 1.0f*mat._42;
	temp.z = Scr.x* mat._13 + Scr.y*mat._23 + Scr.z*mat._33 + 1.0f*mat._43;
	float w = Scr.x* mat._14 + Scr.y*mat._24 + Scr.z*mat._34 + 1.0f*mat._44;
	temp /= w;


	D3DXMatrixIdentity(&mat);
	D3DXMatrixInverse(&mat, NULL, &matView);

	Scr.x = temp.x* mat._11 + temp.y*mat._21 + temp.z*mat._31 + 1.0f*mat._41;
	Scr.y = temp.x* mat._12 + temp.y*mat._22 + temp.z*mat._32 + 1.0f*mat._42;
	Scr.z = temp.x* mat._13 + temp.y*mat._23 + temp.z*mat._33 + 1.0f*mat._43;

	return Scr;
}

Vector3  ScrConverter::Convert_ToScrPos_FromWorldPos(Vector3 World)
{
	Vector3 temp;
	Matrix mat = matView*matProjection;
	temp.x = World.x* mat._11 + World.y*mat._21 + World.z*mat._31 + 1.0f*mat._41;
	temp.y = World.x* mat._12 + World.y*mat._22 + World.z*mat._32 + 1.0f*mat._42;
	temp.z = World.x* mat._13 + World.y*mat._23 + World.z*mat._33 + 1.0f*mat._43;
	float w = World.x* mat._14 + World.y*mat._24 + World.z*mat._34 + 1.0f*mat._44;
	temp.x /= w;
	temp.y /= w;
	if (temp.z >= 0)
		temp.z /= w;

	return temp;
}
