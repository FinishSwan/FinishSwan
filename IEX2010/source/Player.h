#pragma once

#include "BaseObj.h"

class Player:public BaseObjct
{
private:
	 iex3DObj* obj;
	 int state;//モーション用
	float outZ ;
public:
	Player(const float radius, const float adjust_h,
		const Vector3& pos, const Vector3& angle,
		const Vector3& scale,
		const Vector3& color, iex3DObj* insert_skinmesh);
	~Player();
	bool Init(char*filename);
	void Move();
	void SetMotion(int motion);

	float StageWallFront();
	float StageWallBack();
	float StageWallRight();
	float StageWallLeft();


	void Rotate();

	bool Update();
	void Render();
	
	void DebugText();
	//セッター
	void SetPos(const Vector3&pos){ this->pos = pos; }
	void SetAngle(const Vector3&angle){ this->angle = angle; }
	void SetScale(const Vector3&scale){ this->scale = scale; }
	//void SetTarget(const Vector3&target){ this->SetTarget->target; }
	int RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist)override;
	void Collision(const Vector3& hit_position, BaseObjct* hit_object)override;

};

