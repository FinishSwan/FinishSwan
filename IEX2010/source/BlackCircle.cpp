#include	"iextreme.h"
#include	"BlackCircle.h"

void BlackCircle::Update()
{
	if (!enable)
		return;

	time += 1.0f / 60.0f;
}

void BlackCircle::Render()
{
	if (!enable)
		return;

	float max = 1300.0f;
	float rate = time / maxtime;
	float scale = max * rate*rate*rate;

	obj->Render(iexSystem::ScreenWidth / 2 - scale / 2, iexSystem::ScreenHeight / 2 - scale / 2,
		scale, scale, 0, 0, 1024, 1024);
}
BlackCircle::BlackCircle()
{
	obj = new iex2DObj("DATA\\BG\\BlackCircle.png");
	enable = false;
}

void BlackCircle::Start(float time)
{
	if (enable)
		return;

	enable = true;
	this->time = .0f;
	maxtime = time;
}