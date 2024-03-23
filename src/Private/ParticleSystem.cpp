#include "Public/ParticleSystem.h"
#include "Public/Particle.h"

#include "Public/Statics.h"

#include <algorithm>


ParticleSystem::ParticleSystem(const int maxParticleCnt, const int maxSpawnRadius, bool bRandomColor, EParticleSystemType particleSysType,
	const Vector2 position, const Vector2 scaleMinMax, const Color& color) :
	maxParticles(maxParticleCnt),
	maxSpawnRadius(maxSpawnRadius),
	particleSystemType(particleSysType),
	bGenerateRandomParticleColor(bRandomColor),
	GameObject(position, scaleMinMax, color)

{
	bIsSysActive = true;
	bIsParticlesReady = false;
	particlePositionOffset = Vector2Zero();
	particleLifeTimeMinMax = { 1, 1 };

	SpawnParticles();
}

void ParticleSystem::Update(float deltaTime)
{
	DrawParticles();

	if (particleSystemType == EParticleSystemType::EPST_Trail)
	{
		ManageTrailParticles();
	}
	else if (particleSystemType == EParticleSystemType::EPST_Explode)
	{
		if (!bIsParticlesReady)
		{
			PrepareExplotionParticles();
		}
		else
		{
			if (IsAllParticlesDeactive())
			{
				bIsSysActive = false;
				return;
			}

			UpdateParticles(deltaTime);
		}
	}

	ManageParticleLifetime();
}

void ParticleSystem::SpawnParticles()
{
	for (size_t i = 0; i < maxParticles; i++)
	{
		particles.push_back(std::make_unique<Particle>());
	}
}

void ParticleSystem::ManageTrailParticles()
{	
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (!particles[i]->bIsActive)
		{
			particles[i]->bIsActive = true;
			particles[i]->alpha = GameStatics::RandomFloat(particleLifeTimeMinMax.x, particleLifeTimeMinMax.y);
		
			SetParticleColor(particles[i].get());
			
			Vector2 pos = RandomPointInCircle(maxSpawnRadius);
			Vector2 spawnPos = Vector2Add(Vector2Add(owner->position , particlePositionOffset), pos);

			particles[i]->position = spawnPos;
			
			
			particles[i]->scale = {GameStatics::RandomFloat(scale.x,scale.y)};

			break;
		}
	}	
}

void ParticleSystem::PrepareExplotionParticles()
{
	Vector2 upVec = { 0, -1 };
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (!particles[i]->bIsActive)
		{
			particles[i]->bIsActive = true;
			particles[i]->alpha = GameStatics::RandomFloat(1.0f, 10.0f);

			SetParticleColor(particles[i].get());
			
			Vector2 pos = RandomPointInCircle(maxSpawnRadius);

			particles[i]->position = position;
			particles[i]->velocity = Vector2Normalize(pos);
			particles[i]->speed = GameStatics::RandomFloat(50.0f, 200.0f);		

			particles[i]->scale = { GameStatics::RandomFloat(scale.x,scale.y) };	

			particles[i]->SetDrawType((EParticleDrawType)GetRandomValue(0, ((int)EParticleDrawType::EPDT_MAX) - 1));
		}
	}

	bIsParticlesReady = true;
}

void ParticleSystem::ManageParticleLifetime()
{
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i]->bIsActive)
		{
			particles[i]->alpha -= GetFrameTime() * 5;

			if (particles[i]->alpha <= 0.0f)
			{
				particles[i]->bIsActive = false;
			}
		}
	}
}

void ParticleSystem::DrawParticles()
{	
	for (size_t i = 0; i < particles.size(); i++)
	{
		if (particles[i]->bIsActive)
		{
			particles[i]->Draw();
		}
	}	
}

void ParticleSystem::SetParticleColor(Particle* particle)
{
	if (!particle) return;	

	if (!bGenerateRandomParticleColor)
	{
		particle->SetColor(goColor);
	}
	else
	{
		Color rndClr = { GetRandomValue(0, 255), GetRandomValue(0, 255), GetRandomValue(0, 255), 255 };
		particle->SetColor(rndClr);
	}
}

void ParticleSystem::UpdateParticles(float deltaTime)
{
	for(auto& particle : particles)
	{
		if (particle->bIsActive)
		{
			particle->position.x += particle->velocity.x * particle->speed * deltaTime;
			particle->position.y += particle->velocity.y * particle->speed * deltaTime;

			particle->SetColor(Fade(particle->GetColor(), particle->alpha));
		}
	}
}

bool ParticleSystem::IsAllParticlesDeactive()
{
	int deactiveParticleCnt = std::count_if(particles.begin(), particles.end(), 
		[](unique_ptr<Particle>& particle)
		{ 
			return particle->bIsActive == false;
		});

	return particles.size() == deactiveParticleCnt;
}

void ParticleSystem::DeactivateAllParticles()
{
	for (auto& particle : particles)
	{
		particle->bIsActive = false;
	}
}

Vector2 ParticleSystem::RandomPointInCircle(const float radius)
{
	float rndAngle = GameStatics::RandomFloat(0.0f, 359.0f);
	float rndRadius = GameStatics::RandomFloat(0, maxSpawnRadius);
	Vector2 point = Vector2Scale(Vector2Rotate(GameStatics::GetUpVector(), rndAngle), rndRadius);

	return point;
}
