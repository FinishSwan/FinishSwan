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
	//ƒpƒ‰ƒ[ƒ^Ý’è

	float WaveSpeed =300.0f;
	float WavePower = 20.0f;
	float WaveLoopLength = 80.0f;
	float WaveLength = 300.0f;
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
	//WavePower ”g‚Ì‚‚³
	//WaveSpeed ”g‚Ì‘¬“x(1.0f = 1•b1m)
	//WaveMultiple ”g‚ÌŽüŠú(1.0f = 1•b1ŽüŠú)
	//WaveMaxTime ”g‚Ì¶‘¶ŽžŠÔ
	//WaveLossTime ”g‚Ì¶¬‚³‚ê‚Ä‚©‚çŒo‰ß‚µ‚½ŽžŠÔ‚É‚æ‚éŒ¸Š—Í(1.0f = 1•b1.0Œ¸Š)
	//WaveTime ”g‚ÌŒo‰ßŽžŠÔ

	//float LengthSub; //ƒVƒF[ƒ_[ã‚ÅŽg—p‚·‚é•Ï”@‚»‚Ì”g‚Ì¶¬ŽžŠÔ = Length / LengthSub + WaveTime;


	//float Length;

	//Œ»Ý‚Ì”g‚Ì¶¬‚³‚ê‚½ŽžŠÔ‚ð‹‚ß‚é
	//float EmitTime = WaveTime + (Length / WaveSpeed);

	//”g‚ÌŽüŠú‚ðŽæ“¾ (6.28f‚ÅˆêŽü)

	//Wave = sinf(EmitTime *( M_PI * 2.0f) *WaveMultiple);
	float ShaderWaveMultiple = (M_PI * 2.0f) *WaveMultiple;

	//Wave = sinf(EmitTime * ShaderWaveMultiple);

	//float WorkWavePower = WavePower;

	//ŽžŠÔŒ¸Š
	//WorkWavePower *= 1.0f - (EmitTime / WaveMaxTime);

	//‹——£Œ¸Š
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