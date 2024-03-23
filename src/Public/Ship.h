#pragma once
#include "GameObject.h"
#include "Public/IDamageable.h"

class Bullet;
class ParticleSystem;

class Ship : public GameObject, public IDamageable
{
public:
	
	float movementSpeed;

	Vector2 velocity{0,0};

	Vector2 input;

	Ship(const Vector2 position, const Vector2 scale, const Color& color);

	void Draw() override;

	void Update(float deltaTime) override;

	Vector2 GetMuzzlePosition();

	void RotateShip(const Vector2& target);

	void SpawnBullet();

	void ConstraintShipPosition();

	~Ship();

private:

	ParticleSystem* psShipThruster;


public:
	// Inherited via IDamageable
	virtual void OnReceiveHit() override;

};

