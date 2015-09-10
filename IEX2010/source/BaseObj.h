#pragma once

class BaseObjct
{
public:
	BaseObjct(const float radius, const float adjust_h,
		const Vector3& pos, const Vector3& angle,
		const Vector3& scale,
		const Vector3& color);
	virtual ~BaseObjct();
	virtual bool Update() = 0;
	virtual void Render() = 0;
	virtual int RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist) = 0;
	virtual void Collision(const Vector3& hit_position, BaseObjct* hit_object) =0;

	inline Vector3 GetPos(){ return pos; }
	inline Vector3 GetAngle(){ return angle; }
	inline Vector3 GetScale(){ return scale; }
	inline Vector3 GetColor(){ return color; }
	inline Vector3 GetVelocity(){ return velocity; }
	inline float GetRadius(){ return radius; }
	inline float GetAdjust_height(){return adjust_height;}

protected:
	Vector3 pos;
	Vector3 angle;
	Vector3 scale;
	Vector3 color;//�G�ꂽ���̐F
	Vector3 velocity;//�ړ����

	float radius;			//�����蔻�蔼�a
	float adjust_height;	//�����蔻��p�̍��������i���S���狅������j
};