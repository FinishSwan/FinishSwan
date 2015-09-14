class Wave
{
private:
	iexMesh* HitObj;
	float RestTime;
	float MaxTime;
	float Offset;
public:
	Wave():HitObj(nullptr){};
	void Start_Wave(Vector3 pos, Vector3 dir);//ƒŒƒC‚ğ‚Ô‚Â‚¯‚Ä”g‚ğo‚·
	void Wave_Setting_Param(float WaveTime, float WaveLength, float WaveMaxTime, float WaveMultiple,float WaveSpeed, float WavePower);
	void Update();
	void Render();
	bool IsRender(iexMesh* mesh);	//‚±‚ÌƒƒbƒVƒ…‚ğ”g‚Í•`‰æ‚·‚é‚©


};