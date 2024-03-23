#include "Public/Particle.h"

Particle::Particle(const Vector2 position, const Vector2 scale, const Color& color, float alpha, bool bActive, const EParticleDrawType drawType) :
	GameObject(position,scale,color), alpha(alpha), bIsActive(bActive), particleDrawType(drawType)
{
}

void Particle::Draw()
{
	switch (particleDrawType)
	{
	case EParticleDrawType::EPDT_Circle:
	{
		DrawCircleV(position, scale.x, goColor);
		break;
	}
	case EParticleDrawType::EPDT_Rectangle:
	{
		DrawPoly(position, 4, scale.x, rotation, goColor);
		break;
	}
	case EParticleDrawType::EPDT_Triangle:
		DrawPoly(position, 3, scale.x, rotation, goColor);
		break;	
	}
}

void Particle::Update(float deltaTime)
{
}
