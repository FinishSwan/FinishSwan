#pragma once

class Camera:public iexView
{
private:
protected:
	Vector3 pos;		//位置
	Vector3 angle;		//向き
	Vector3 target;		//注視点
	Vector3 cpos;
	static const int max = 100;	//最大距離
	static const int min = 10;	//最低距離
public:
	Camera();
	~Camera();
	void Move();//カメラ確認用
	void Directional();
	
	void Update();
	
	void SetPos(const Vector3 pos){ this->pos = pos; }
	void SetAngle(Vector3 angle){ this->angle = angle; }
	void SetTarget(const Vector3&target){ this->target = target; }

	Vector3 GetPos(){ return pos; }
	Vector3 GetAngle()
	{
		angle= target - pos;
		angle.y = 0;
	}
	Vector3 GetTarget(){ return target; }


};



