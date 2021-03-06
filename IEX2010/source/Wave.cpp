#include	"iextreme.h"
#include	"system/Scene.h"
#include	"sceneMain.h"
#include	"BaseObj.h"
#include	"ObjectManager.h"
#include	"Wave.h"


#define _USE_MATH_DEFINES
#include	<cmath>

#include	"system\System.h"


void Wave::Start_Wave(Vector3 pos, Vector3 dir, float power, float length)
{
	if (RestTime > .0f)
		return;
	float Dist = 10000.0f;
	//コリジョンチェック
	struct
	{
		Vector3 out;
		Vector3 vec;
		float dist;
		float length;
		BaseObjct* ret;
	}min, def, work;

	def.vec = dir;
	def.vec.Normalize();
	def.dist = 10000.0f;
	def.out = def.vec * def.dist;


	BaseObjct::TYPE types[3] =
	{
		BaseObjct::TYPE::judge,
		BaseObjct::TYPE::floor,
		BaseObjct::TYPE::wall
	};
	for (size_t i = 0; i < 3; i++)
	{
		work = def;
		work.ret = obj_manager.Collision_of_RayPick(&work.out, &pos, &work.vec, &work.dist, nullptr, types[i]);
		work.length = (pos - work.out).Length();
		if (i == 0 || work.length < min.length)
		{
			min = work;
		}
	}

	if (min.length < 7.0f)
	{
		if (min.ret == nullptr)
			return;
		if (min.ret->IsPainted())
			return;
		HitObj = min.ret;
		MaxTime = 1.0f;
		RestTime = MaxTime;
		Offset = .0f;
		shader->SetValue("WavePos", min.out);
		Power = power;
		Length = length;
	}

	//if (stage->RayPick(&out, &pos, &dir, &Dist) != -1)
	//{

	//}



}

void	Wave::Update()
{
	const float MaxLength = 60.0f;
	const float MaxPower = .8f;
	RestTime -=1.0f / 60.0f;
	Offset += 1.0f / 60.0f * 1.0f;
	
	float rate = RestTime / MaxTime;
	//パラメータ設定

	float WaveSpeed =150.0f;
	float WavePower = /*10.0f;*/Power;
	float WaveLoopLength = 40.0f;
	float WaveLength = /*150.0f*/Length;
	float WaveMaxTime = 1.4f;
	float WaveMultiple = WaveSpeed / WaveLoopLength;
	float WaveLossTime = WavePower / (WaveLoopLength / WaveSpeed);


	Wave_Setting_Param(Offset, WaveLossTime, WaveMaxTime, WaveMultiple, WaveSpeed, WavePower);
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

	if (HitObj == nullptr)
		return;

	if (HitObj->IsPainted())
		return;

		HitObj->Wave_Render();
}


bool	Wave::IsRender(BaseObjct* mesh)
{
	if (mesh != HitObj)
		return false;

	if (HitObj == nullptr)
		return false;

	return !HitObj->IsPainted();
}