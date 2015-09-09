#pragma once

class Camera:public iexView
{
private:
protected:
	Vector3 pos;		//�ʒu
	Vector3 angle;		//����
	Vector3 target;		//�����_
	static const int max = 100;	//�ő勗��
	static const int min = 10;	//�Œ዗��
public:
	Camera();
	~Camera();
	void Directional();
	
	void Update();
	
	void SetPos(const Vector3 pos)
	{
		this->pos = pos;
	}

	void SetAngle(Vector3 angle)
	{
		this->angle = angle;
	}

	void SetTarget(const Vector3&target)
	{
		this->target = target;
	}

	Vector3 GetPos(){ return pos; }
	Vector3 GetTarget(){ return target; }


};



