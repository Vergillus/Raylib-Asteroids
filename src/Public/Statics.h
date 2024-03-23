#pragma once

#include <vector>
#include <memory>
#include "raymath.h"

using std::vector;

class GameObject;
class ParticleSystem;

class GameStatics
{
public:

	constexpr static int screenWidth = 800;
	constexpr static int screenHeight = 600;

	constexpr static float halfScreenWidth = screenWidth / 2.0f;
	constexpr static float halfScreenHeight = screenHeight / 2.0f;

	static vector<std::shared_ptr<GameObject>> spawnedBullets;
	static vector<std::shared_ptr<ParticleSystem>> particleSystemsToManage;

	static float RandomFloat(float min, float max);

	static Vector2 GetUpVector() { return { 0, -1 }; };
	static Vector2 GetDownVector() { return { 0, 1 }; };
	static Vector2 GetLeftVector() { return { -1, 0 }; };
	static Vector2 GetRightVector() { return { 1, 0 }; };

};