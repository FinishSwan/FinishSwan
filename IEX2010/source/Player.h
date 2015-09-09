#pragma once
#include "BaseObj.h"

class Player:public BaseObjct
{
private:
	 iex3DObj* obj;
	 int state;//モーション用
public:
	Player();
	~Player();
	bool Init(char*filename);
	void Move(Vector3 cpos,Vector3 ctarget);
	void SetMotion(int motion);
	bool Update();
	void Render();
	

	//セッター
	void SetPos(const Vector3&pos){ this->pos = pos; }
	void SetAngle(const Vector3&angle){ this->angle = angle; }
	void SetScale(const Vector3&scale){ this->scale = scale; }
	//void SetTarget(const Vector3&target){ this->SetTarget->target; }
};

