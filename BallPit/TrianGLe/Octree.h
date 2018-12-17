#pragma once
#include "Include.h"
#include "Ball.h"
class Octree
{
public:
	Octree(vec3 location, vec3 maxDistances, Octree* creator = nullptr);
	~Octree();

	//Variables
	vec3 position;
	vec3 bounds;

	const int maxBalls = 8;
	vector<Ball*> balls;

	Octree** children = nullptr;
	Octree* parent = nullptr;

	//Functions
	void Update();
	void Render();

	void AddBall(Ball* ball);
	void RemoveBall(Ball* ball);
	int CountBalls();

	void Subdivide();
	void Collapse();
	bool InRegion(Ball* ball, Octree* region);
};

