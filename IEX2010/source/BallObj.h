class BaseObjct;

class Ball :public BaseObjct
{
private:
	iexMesh* obj;
	Vector3 move;
	bool	enable;
public:
	Ball(const float radius, const float adjust_h,
		const Vector3& pos, const Vector3& angle,
		const Vector3& scale,
		const Vector3& color,
		BaseObjct::TYPE t,
		iexMesh* insert_mesh);
	~Ball();
	bool Init(char*filename);
	bool Update();
	void Render();
	void Wave_Render()override{};

	void Ball_Start(Vector3 pos,Vector3 move);
	//void SetTarget(const Vector3&target){ this->SetTarget->target; }
	int RayPick(Vector3* out, Vector3* pos, Vector3* vec, float *Dist)override;
	void Collision(const Vector3& hit_position, BaseObjct* hit_object)override;

};

