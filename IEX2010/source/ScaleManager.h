#pragma once

#include <map>

class ScaleManager
{
private:
	static std::map<char*, float >scalemap;
public:
	static bool Register(char* registername, const float registerscale);
	static float GetScale(char* modelname);
};