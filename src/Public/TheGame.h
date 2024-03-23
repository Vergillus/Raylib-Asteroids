#pragma once

#include "raylib.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <mutex>

using std::cout;
using std::vector;
using std::unique_ptr;

class Ship;
class Enemy;

struct Star
{
	Vector2 position;
	Vector2 scale;
	Color color;
	float alpha;
	int8_t alphaMulti;
};

class TheGame
{
	enum class EDirections
	{
		ED_UP,
		ED_DOWN,
		ED_LEFT,
		ED_RIGHT,

		D_MAX
	};

	enum class EGameState
	{
		EGS_Start,
		EGS_Play,
		EGS_GameOver,

		EGS_MAX
	};

public:

	TheGame();

	void Run();

	Vector2 ManageKeyboardInput();

	void ManageGameObjectsLifeTime();

	void ManageGameObjectsLifetimeThread();

	void ManageStars(float deltaTime);	
	
	void ManageEnemy();

	void ManageGameObjects(float deltaTime);	

	void ManageGameUI();

	void CollisionsCheck();
	void CollisionsCheckThread();

	void ResetEnemy(Enemy* enemy, Vector2& targetPos);

	void ResetScene();

	void ManageDelayedSceneReset(const Color& bgColor);

	Vector2 GetRandomPositionOnScreenBoundaries();

	void RenderMenuScene();
	void RenderGameScene();
	void RenderGameOverScene();

	~TheGame();

private:
	Ship* spaceShip;

	vector<unique_ptr<Enemy>> enemies;
	vector<Star> stars;	

	EGameState gameState;

	float deltaTime = 0.0f;

	float enemyActivationTimer = 2.0f;
	int enemyActivationIndex = 0;

	bool bIsSceneResetNeeded = false;
	float sceneResetDelay = 3.0f;

	const Color bgColor = Color{ 39, 55, 77, 255 };

	std::mutex manageGOMutex;
	std::mutex collisionCheckMutex;
};

