#pragma once

#include "Public/GameObject.h"

#include "raymath.h"
#include "raylib.h"

#include <memory>
#include <vector>

using std::vector;
using std::unique_ptr;

class Particle;


enum class EParticleSystemType
{
	EPST_Trail,
	EPST_Explode,

	EPST_None
};

class ParticleSystem : public GameObject
{
public:

	int maxParticles;		
	float maxSpawnRadius;
	bool bIsSysActive;

	Vector2 particlePositionOffset;
	Vector2 particleLifeTimeMinMax;

	GameObject* owner;

	ParticleSystem(const int maxParticleCnt, const int maxSpawnRadius, bool bRandomColor, EParticleSystemType particleSysType, const Vector2 position, const Vector2 scaleMinMax, const Color& color = MAGENTA);

	void Update(float deltaTime) override;

	void SpawnParticles();

	void DeactivateAllParticles();

private:

	bool bGenerateRandomParticleColor;
	bool bIsParticlesReady;

	EParticleSystemType particleSystemType;
	vector<unique_ptr<Particle>> particles;

	void ManageTrailParticles();
	void PrepareExplotionParticles();
	void ManageParticleLifetime();
	void DrawParticles();

	void SetParticleColor(Particle* particle);

	void UpdateParticles(float deltaTime);

	bool IsAllParticlesDeactive();

	Vector2 RandomPointInCircle(const float radius);
};

