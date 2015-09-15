#pragma once

#include "BaseObj.h"

class Fileobject:public BaseObjct
{
public:
	Fileobject(const float radius, const float adjust_h,
		const Vector3& pos, const Vector3& angle,
		const Vector3& scale,
		const Vector3& color,
		const TYPE type,
		iexMesh* mesh);
	~Fileobject();
	bool Update()override;
	void Render()override;
	int RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist) override;
	void Collision(const Vector3& hit_position, BaseObjct* hit_object) override;


private:
	iexMesh* mesh;

};