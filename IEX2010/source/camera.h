#pragma once

class Camera:public iexView
{
private:
protected:
	Vector3 pos;		//�ʒu
	Vector3 angle;		//����
	Vector3 target;		//�����_
	Vector3 cpos;
	static const int max = 100;	//�ő勗��
	static const int min = 10;	//�Œ዗��
public:
	Camera();
	~Camera();
	void Move();//�J�����m�F�p
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



