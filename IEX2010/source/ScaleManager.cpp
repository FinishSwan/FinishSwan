#include "iextreme.h"
#include "ScaleManager.h"

std::map<char*, float> ScaleManager::scalemap;

bool ScaleManager::Register(char* registername, const float registerscale)
{
	scalemap.insert(std::pair<char*, float>(registername, registerscale));
	return true;
}

float ScaleManager::GetScale(char* modelname)
{
	if (scalemap.find(modelname) == scalemap.end())
	{
		return -1;
	}
	return scalemap[modelname];
}
