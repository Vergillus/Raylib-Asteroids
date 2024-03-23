#include "Public/GameObject.h"

#include "raymath.h"

GameObject::GameObject(const Vector2 position, const Vector2 scale, const Color& color) :
	position(position),
	scale(scale),
	goColor(color)
{	
	lifeTime = 1;
	forward = Vector2{ 0,-1 };
}

