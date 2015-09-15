#pragma once 

#include <random>
#include <Windows.h>

class RandomEngine
{
public :
	static void Initialize();
	template<class T =int>
	static int Execute(const T min,const T max)
	{
		std::uniform_int_distribution<T> dist(min, max);
		return dist(mt_rand);
	}

private :
	static ULONG seed[4];
	static std::mt19937 mt_rand;
	
	
};