#pragma once

class BaseObjct
{
public:

	enum TYPE
	{
		all,
		judge,//³‰ğ
		floor,	//°
		player,//ƒvƒŒƒCƒ„[
		wall//•Ç
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
	Vector3 color;//G‚ê‚½‚ÌF
	Vector3 velocity;//ˆÚ“®î•ñ
	TYPE type;
	
	Vector3 PaintPos;	//“h‚ç‚ê‚éˆÊ’u
	float PaintRange;	//“h‚ç‚ê‚é”ÍˆÍ
	bool	Painted;	//“h‚ç‚ê‚½ƒtƒ‰ƒO

	float radius;			//“–‚½‚è”»’è”¼Œa
	float adjust_height;	//“–‚½‚è”»’è—p‚Ì‚‚³’²®i’†S‚©‚ç‹…”»’è‚â‚éj

	void Paint_Update();
	bool Paint_Render(iexMesh* mesh);	//•`‰æ‚³‚ê‚È‚©‚Á‚½‚çfalse
	void Wave_Render(iexMesh* mesh);	//”g‚Ì•`‰æ
};