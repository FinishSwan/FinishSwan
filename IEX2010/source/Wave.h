class Wave
{
private:
	iexMesh* HitObj;
	float RestTime;
	float MaxTime;
	float Offset;
public:
	Wave():HitObj(nullptr){};
	void Start_Wave(Vector3 pos, Vector3 dir);//���C���Ԃ��Ĕg���o��
	void Wave_Setting_Param(float WaveTime, float WaveLength, float WaveMaxTime, float WaveMultiple,float WaveSpeed, float WavePower);
	void Update();
	void Render();
	bool IsRender(iexMesh* mesh);	//���̃��b�V����g�͕`�悷�邩


};