#pragma once
#include "Shape.h"
class Ball : public Shape
{
public:
	Ball(bool isDynamic, float collRadius, float shapeMass = 1.f, float xPos = 0, float yPos = 0, float zPos = 0);
	~Ball();

	float radius;

	bool CollidesWith(Ball* other);
	void ResolveCollision(Ball* other);
	bool OutOfBounds();
	void Rebound();
	void Shrink(float scale);

	void SetVertices();
};

