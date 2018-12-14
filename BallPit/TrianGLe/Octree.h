#pragma once
#include "Include.h"
class Octree
{
public:
	Octree(vec3 location, vec3 maxDistances, Octree* creator = nullptr);
	~Octree();

	//Variables
	vec3 position;
	vec3 bounds;

	const int maxShapes = 8;
	vector<Shape*> shapes;
	Octree** children = nullptr;
	Octree* parent = nullptr;

	//Functions
	void Update();

	void AddShape(Shape* shape);
	void RemoveShape(Shape* shape);
	int CountShapes();

	void Subdivide();
	void Collapse();
};

