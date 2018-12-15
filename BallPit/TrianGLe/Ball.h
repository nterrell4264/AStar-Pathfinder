#pragma once
#include "Include.h"
#include "Shape.h"
class Ball : public Shape
{
public:
	Ball(bool isDynamic, float collRadius, float shapeMass = 1.f, float xPos = 0, float yPos = 0, float zPos = 0);
	~Ball();

	float radius;

	void SetVertices();
};

