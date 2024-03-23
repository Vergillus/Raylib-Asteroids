#pragma once

#include "Public/GameObject.h"

#include <vector>

class Particle;
class ParticleSystem;

class Bullet : public GameObject
{
public:

	float speed;
	Vector2 movementDir;

	Bullet(const Vector2 position, const Vector2 scale, const Color& color);

	void Draw() override;

	void Update(float deltaTime) override;	

	~Bullet();

private:
	ParticleSystem* particleSystem;
};
