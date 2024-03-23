#include "Public/Bullet.h"
#include "Public/Statics.h"
#include "Public/Particle.h"
#include "Public/ParticleSystem.h"

#include "raymath.h"


#include <iostream>


Bullet::Bullet(const Vector2 position, const Vector2 scale, const Color& color) :
	GameObject(position, scale, color)
{
	speed = 0;
	movementDir = { 0,0 };	
	
	particleSystem = new ParticleSystem(20, 10, false, EParticleSystemType::EPST_Trail, position, { 1.0f,5.0f }, ColorAlpha(BEIGE, 0.5f));
	if (particleSystem)
	{
		particleSystem->owner = this;
	}	
}

void Bullet::Draw()
{
	DrawCircleV(position, scale.x, goColor);
}

void Bullet::Update(float deltaTime)
{
	position.x += movementDir.x * speed * deltaTime;
	position.y += movementDir.y * speed * deltaTime;

	lifeTime = std::max(0.0f, lifeTime - deltaTime);	


	if (particleSystem)
	{
		particleSystem->Update(deltaTime);
	}
}

Bullet::~Bullet()
{
	if (particleSystem)
	{
		delete particleSystem;
	}
}

