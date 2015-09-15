#pragma once

class BaseObjct
{
public:

	enum TYPE
	{
		all,
		judge,//正解
		floor,	//床
		player,//プレイヤー
		wall//壁
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




protected:
	Vector3 pos;
	Vector3 angle;
	Vector3 scale;
	Vector3 color;//触れた時の色
	Vector3 velocity;//移動情報
	TYPE type;
	
	Vector3 PaintPos;	//塗られる位置
	float PaintRange;	//塗られる範囲
	bool	Painted;	//塗られたフラグ

	float radius;			//当たり判定半径
	float adjust_height;	//当たり判定用の高さ調整（中心から球判定やる）

	void Paint_Update();
	bool Paint_Render(iexMesh* mesh);	//描画されなかったらfalse
};