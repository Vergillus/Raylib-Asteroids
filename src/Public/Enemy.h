#pragma once
#include "GameObject.h"
#include "Public/IDamageable.h"

class Enemy : public GameObject, public IDamageable
{
public:

	float speed;
	Vector2 movementDir;

	Color goColor2;

	Enemy(const Vector2 position, const Vector2 scale, const Color& color, const Color& color2, const Vector2& targetPosition, float speed);

	void Draw() override;

	void Update(float deltaTime) override;


	// Inherited via IDamageable
	virtual void OnReceiveHit() override;

	void ReInitializeEnemy(const Vector2 position, const Vector2 scale, const Vector2& targetPosition);

};

