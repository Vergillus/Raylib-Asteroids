#pragma once
#include "GameObject.h"

enum class EParticleDrawType
{
	EPDT_Circle,
	EPDT_Rectangle,
	EPDT_Triangle,

	EPDT_MAX
};

class Particle : public GameObject
{
public:
	float alpha;
	float speed;
	bool bIsActive;	
	Vector2 velocity;

	Particle(const Vector2 position = Vector2{ 0,0 }, const Vector2 scale = Vector2{ 1,1 },
		const Color& color = GRAY, float alpha = 1, bool bActive = false, const EParticleDrawType drawType = EParticleDrawType::EPDT_Circle);

	void Draw() override;
	void Update(float deltaTime) override;

	inline void SetDrawType(const EParticleDrawType drawType) { particleDrawType = drawType; }

protected:
	EParticleDrawType particleDrawType;

};

