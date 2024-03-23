#include "Public/Statics.h"

#include <random>

//constexpr int GameStatics::screenWidth = 800;
//constexpr int GameStatics::screenHeight = 600;
//
//constexpr float GameStatics::halfScreenWidth = screenWidth / 2.0f;
//constexpr float GameStatics::halfScreenHeight = screenHeight / 2.0f;

vector<std::shared_ptr<GameObject>> GameStatics::spawnedBullets;
vector<std::shared_ptr<ParticleSystem>> GameStatics::particleSystemsToManage;

float GameStatics::RandomFloat(float min, float max)
{
	/*if(max < min) return 0;

	float random = (float)rand() / (float)RAND_MAX;
	
	float range = max - min;
	return (random * range) + min;*/

	if (min == max) return min;

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> dist(min, max);

	return dist(gen);
}