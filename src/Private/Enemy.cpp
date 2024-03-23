#include "Public/Enemy.h"
#include "Public/ParticleSystem.h"
#include "Public/Statics.h"

#include "raymath.h"

#include <iostream>
#include <memory>

#include "Public/Global.h"

Enemy::Enemy(const Vector2 position, const Vector2 scale, const Color& color, const Color& color2, const Vector2& targetPosition, float speed) :
	GameObject(position,scale,color), goColor2(color2), speed(speed)
{
	/*movementDir = Vector2Normalize(Vector2Subtract(targetPosition, position));
	
	lifeTime = 3.0f;*/
	lifeTime = 0.0f;
}

void Enemy::Draw()
{
	DrawCircleGradient(position.x, position.y, scale.x, goColor, goColor2);
}

void Enemy::Update(float deltaTime)
{
	position.x += movementDir.x * speed * deltaTime;
	position.y += movementDir.y * speed * deltaTime;
}

void Enemy::OnReceiveHit()
{
	static Color clr = { 155, 171, 184,255 };
	std::shared_ptr<ParticleSystem> explotionParticle = std::make_shared<ParticleSystem>(50, 30, false, EParticleSystemType::EPST_Explode, position, Vector2{ 1,5 }, ColorAlpha(clr, 0.5f));
	if (explotionParticle)
	{
		GameStatics::particleSystemsToManage.push_back(explotionParticle);
	}

	lifeTime = 0;
	
	global.playerScore++;
}

void Enemy::ReInitializeEnemy(const Vector2 position, const Vector2 scale, const Vector2& targetPosition)
{
	movementDir = Vector2Normalize(Vector2Subtract(targetPosition, position));
	lifeTime = 3.5f;
	this->position = position;
	this->scale = scale;
}
