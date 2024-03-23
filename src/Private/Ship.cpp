#include "Public/Ship.h"
#include "Public/Bullet.h"
#include "Public/Statics.h"
#include "Public/ParticleSystem.h"
#include "Public/Global.h"

#include "raymath.h"

Ship::Ship(const Vector2 position, const Vector2 scale, const Color& color)
	: GameObject(position, scale, color) 
{
	rotation = 180;
	input = { 0,0 };
	movementSpeed = 0;

	psShipThruster = new ParticleSystem(20, 5, true, EParticleSystemType::EPST_Trail, position, { 1.0f,5.0f }, DARKPURPLE);
	if (psShipThruster)
	{
		psShipThruster->owner = this;
		psShipThruster->particleLifeTimeMinMax = { 1.0f, 5.0f };
	}
}

void Ship::Draw()
{
	DrawPoly(position, 3, scale.x, rotation, goColor);	
}

void Ship::Update(float deltaTime)
{
	ConstraintShipPosition();

	if (input.x != 0 || input.y != 0)
	{
		velocity.x = input.x * movementSpeed;
		velocity.y = input.y * movementSpeed;			
	}
	else
	{			
		velocity.x *= fabsf(velocity.x) > 5.0f ? 0.98f : 0.0f;
		velocity.y *= fabsf(velocity.y) > 5.0f ? 0.98f : 0.0f;		
	}

	position.x += velocity.x * deltaTime;
	position.y += velocity.y * deltaTime;	

	if (psShipThruster)
	{
		psShipThruster->particlePositionOffset = Vector2Scale(forward, -scale.x * 0.5f);
		psShipThruster->Update(deltaTime);
	}
}

Vector2 Ship::GetMuzzlePosition()
{
	return Vector2Add(position, Vector2Scale(forward, 15));
}

void Ship::RotateShip(const Vector2& target)
{
	Vector2 lookAtDir = Vector2Normalize(Vector2Subtract(target, position));
	float angle = atan2f(lookAtDir.y, lookAtDir.x) * RAD2DEG;
	rotation = 89 - angle;

	forward = lookAtDir;

}

void Ship::SpawnBullet()
{
	std::unique_ptr<Bullet> spawnedBullet = std::make_unique<Bullet>(GetMuzzlePosition(),Vector2{5},BLACK);
	if (spawnedBullet)
	{
		spawnedBullet->movementDir = forward;
		spawnedBullet->speed = 700.0f;		
		spawnedBullet->SetLifeTime(2.0f);

		GameStatics::spawnedBullets.emplace_back(std::move(spawnedBullet));
	}
}

void Ship::ConstraintShipPosition()
{
	if (position.x > GameStatics::screenWidth)
	{
		position.x = 0;
	}
	else if (position.x < 0)
	{
		position.x = GameStatics::screenWidth;
	}
	else if (position.y > GameStatics::screenHeight)
	{
		position.y = 0;
	}
	else if (position.y < 0)
	{
		position.y = GameStatics::screenHeight;
	}
}


void Ship::OnReceiveHit()
{
	global.playerLifes = std::max(0, global.playerLifes - 1);
	
	position = { GameStatics::halfScreenWidth, GameStatics::halfScreenHeight };

	if (psShipThruster)
	{
		psShipThruster->DeactivateAllParticles();
	}
}


Ship::~Ship()
{
	if (psShipThruster) delete psShipThruster;
}