#pragma once

#include "raylib.h"

#include <iostream>


class GameObject
{
public:

	Vector2 position;
	Vector2 scale;	
	Vector2 forward;

	float rotation;

	GameObject(const Vector2 position = Vector2{0,0}, const Vector2 scale = Vector2{1,1}, const Color& color = GRAY);

	virtual void Draw() {};

	virtual void Update(float deltaTime) {};

	inline float GetLifeTime() const { return lifeTime; }
	inline void SetLifeTime(float newLifeTime) { lifeTime = newLifeTime; }
	inline Color GetColor() const { return goColor; }
	inline void SetColor(const Color& newColor) { goColor = newColor; }	

	virtual ~GameObject() = default;

protected:
	float lifeTime;

	Color goColor;

private:

};

