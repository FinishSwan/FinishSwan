#pragma once

class BaseObjct
{
public:

	enum TYPE
	{
		all,
		judge,//����
		floor,	//��
		player,//�v���C���[
		wall//��
	};

	BaseObjct(const float radius, const float adjust_h,
		const Vector3& pos, const Vector3& angle,
		const Vector3& scale,
		const Vector3& color,
		const TYPE type );

	virtual ~BaseObjct();
	virtual bool Base_Update();
	virtual bool Update() = 0;
	virtual void Render() = 0;
	virtual int RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist) = 0;
	virtual void Collision(const Vector3& hit_position, BaseObjct* hit_object) =0;
	virtual void Wave_Render() = 0;
	virtual iexMesh* getMesh(){ return nullptr; }

	void Paint_Start(Vector3 pos);




	bool IsType(TYPE CheckType)
	{
		if (type == CheckType)
		{
			return true;
		}
		return false;
	}


	inline Vector3 GetPos(){ return pos; }
	inline Vector3 GetAngle(){ return angle; }
	inline Vector3 GetScale(){ return scale; }
	inline Vector3 GetColor(){ return color; }
	inline Vector3 GetVelocity(){ return velocity; }
	inline float GetRadius(){ return radius; }
	inline float GetAdjust_height(){return adjust_height;}

	bool IsPainted();

	


protected:
	Vector3 pos;
	Vector3 angle;
	Vector3 scale;
	Vector3 color;//�G�ꂽ���̐F
	Vector3 velocity;//�ړ����
	TYPE type;
	
	Vector3 PaintPos;	//�h����ʒu
	float PaintRange;	//�h����͈�
	bool	Painted;	//�h��ꂽ�t���O

	float radius;			//�����蔻�蔼�a
	float adjust_height;	//�����蔻��p�̍��������i���S���狅������j

	void Paint_Update();
	bool Paint_Render(iexMesh* mesh);	//�`�悳��Ȃ�������false
	void Wave_Render(iexMesh* mesh);	//�g�̕`��
};