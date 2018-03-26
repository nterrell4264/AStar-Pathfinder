#pragma once
#include <vector>
#include "Vector.h"
class Graph
{
public:
	Graph();
	~Graph();

	int* start[2];
	int* end[2];
	vector<Vector> path = nullptr;
	int currentPathIndex = 0;

	void CalculatePath();
};

