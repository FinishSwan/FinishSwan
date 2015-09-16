#include "iextreme.h"
#include "EntryPoint.h"
#include <assert.h>

#include	"CP11Rand.h"

EntryPoint::Positioning EntryPoint::container[15];
int EntryPoint::numactive = 0;

void EntryPoint::Initialize()
{
	
}

bool EntryPoint::Register(const Vector3& pos, const Vector3& angle)
{
	for (int i = 0; i < 15; i++)
	{
		if (container[i].Isactive == false)
		{
			container[i].pos=pos;
			container[i].angle = angle;
			container[i].Isactive = true;
			numactive++;
			return true;
		}
	}
	return false;
}

void EntryPoint::GetPoint(Vector3* outpos, Vector3* outangle)
{
	//int num = rand() % numactive;
	int num = RandomEngine::Execute(0, numactive -1);

	for (int i = 0; i < 15; i++)
	{
		if (container[i].Isactive == false)
			continue;
		
		if (num <= 0)
		{
			*outpos = container[i].pos;
			*outangle = container[i].angle;
			container[i].Isactive = false;
			numactive--;
			return;
		}
		num--;
	}
	assert(false);
}

void EntryPoint::Release()
{
    for (int i = 0; i < 15; i++)
    {
        container[i].Isactive = false;
    }
}
