class BaseObjct;

class Wave
{
private:
	BaseObjct* HitObj;
	float RestTime;
	float MaxTime;
	float Offset;
	float Power;
	float Length;
public:
	Wave():HitObj(nullptr){};
	void Reset(){ HitObj = nullptr; }
	void Start_Wave(Vector3 pos, Vector3 dir,float power,float length);//���C���Ԃ��Ĕg���o��
	void Wave_Setting_Param(float WaveTime, float WaveLength, float WaveMaxTime, float WaveMultiple,float WaveSpeed, float WavePower);
	void Update();
	void Render();
	bool IsRender(BaseObjct* mesh);	//���̃��b�V����g�͕`�悷�邩

};

extern Wave* wave;