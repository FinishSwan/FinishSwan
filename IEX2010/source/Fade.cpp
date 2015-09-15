#include	"Fade.h"
#include	"iextreme.h"

float FadeManager::FadeStartVal = .0f;
float FadeManager::FadeEndVal;
float FadeManager::FadeMaxTime;
float FadeManager::FadeTime;
float FadeManager::FadeVal = 1.0f;

void  FadeManager::Fade_Start(float StartVal, float EndVal, float Time)
{
	FadeStartVal = StartVal;
	FadeEndVal = EndVal;
	FadeTime = .0f;
	FadeMaxTime = Time;
}


void  FadeManager::FadeIn(float Time)
{
	Fade_Start(.0f, 1.0f, Time);
}
void  FadeManager::FadeOut(float Time)
{
	Fade_Start(1.0f, .0f, Time);
}

void  FadeManager::Update()
{
	FadeTime += 1.0f / 60.0f;
	if (FadeTime > FadeMaxTime)
	{
		FadeTime = FadeMaxTime;
	}
	float rate = FadeTime / FadeMaxTime;

	float sub = FadeEndVal - FadeStartVal;

	FadeVal = sub * rate + FadeStartVal;
}

void  FadeManager::Render()
{
	DWORD color = 0x00FFFFFF;
	color |= (unsigned int)(FadeVal * 255.0f) << 24;
	iexPolygon::Rect(0, 0, iexSystem::ScreenWidth, iexSystem::ScreenHeight, RS_ADD, color);

}