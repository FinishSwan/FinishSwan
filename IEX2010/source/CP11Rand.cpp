#include	"CP11Rand.h"

ULONG RandomEngine::seed[4];
std::mt19937 RandomEngine::mt_rand;

void	RandomEngine::Initialize()
{
	std::random_device device;
	for (UINT i = 0; i < 4; i++)
	{
		ULONG r = device();
		seed[i] = 1812433253U * (r ^ (r >> 30)) + i;
	}
	mt_rand.seed(device());
}
