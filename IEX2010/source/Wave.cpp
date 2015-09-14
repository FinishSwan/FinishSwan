#include	"iextreme.h"
#include	"system/Scene.h"
#include	"sceneMain.h"
#include	"Wave.h"

#define _USE_MATH_DEFINES
#include	<cmath>

#include	"system\System.h"


void Wave::Start_Wave(Vector3 pos, Vector3 dir)
{
	Vector3 out;
	float Dist = 10000.0f;
	if (stage->RayPick(&out, &pos, &dir, &Dist) != -1)
	{
		HitObj = stage;
		MaxTime = 1.0f;
		RestTime = MaxTime;
		Offset = .0f;
		shader->SetValue("WavePos", out);
	}



}

void	Wave::Update()
{
	const float MaxLength = 60.0f;
	const float MaxPower = .8f;
	RestTime -=1.0f / 60.0f;
	Offset += 1.0f / 60.0f * 1.0f;
	
	float rate = RestTime / MaxTime;
	//パラメータ設定

	Wave_Setting_Param(Offset,36.0f,1.2f,7.0f,400.0f,13.0f);

	//shader->SetValue("WaveLangth", rate *MaxLength);
	//shader->SetValue("WavePower", rate *MaxPower);
	static float off = .0f;
	if (KEY_Get(KEY_A))
		off += 0.01f;
	printf("%f\n", off);
	shader->SetValue("WaveOffSet", (float)M_PI / 2.0f);


}
void	Wave::Wave_Setting_Param(float WaveTime, float WaveLossTime, float WaveMaxTime, float WaveMultiple, float WaveSpeed, float WavePower)
{
	//WavePower 波の高さ
	//WaveSpeed 波の速度(1.0f = 1秒1m)
	//WaveMultiple 波の周期(1.0f = 1秒1周期)
	//WaveMaxTime 波の生存時間
	//WaveLossTime 波の生成されてから経過した時間による減衰力(1.0f = 1秒1.0減衰)
	//WaveTime 波の経過時間

	//float LengthSub; //シェーダー上で使用する変数　その波の生成時間 = Length / LengthSub + WaveTime;


	//float Length;

	//現在の波の生成された時間を求める
	//float EmitTime = WaveTime + (Length / WaveSpeed);

	//波の周期を取得 (6.28fで一周)

	//Wave = sinf(EmitTime *( M_PI * 2.0f) *WaveMultiple);
	float ShaderWaveMultiple = (M_PI * 2.0f) *WaveMultiple;

	//Wave = sinf(EmitTime * ShaderWaveMultiple);

	//float WorkWavePower = WavePower;

	//時間減衰
	//WorkWavePower *= 1.0f - (EmitTime / WaveMaxTime);

	//距離減衰
	//WorkWavePower -= WaveLossTime * Length;

	//Wave *= WorkWavePower;

	shader->SetValue("WaveLossTime", WaveLossTime);
	shader->SetValue("WavePower", WavePower);
	shader->SetValue("WaveSpeed", WaveSpeed);
	shader->SetValue("WaveMul", ShaderWaveMultiple);
	shader->SetValue("WaveMaxTime", WaveMaxTime);
	shader->SetValue("WaveTime", WaveTime);



}

void	Wave::Render()
{

	if (HitObj != nullptr)
		HitObj->Render(shader, "wave");
}


bool	Wave::IsRender(iexMesh* mesh)
{
	return mesh == HitObj;
}