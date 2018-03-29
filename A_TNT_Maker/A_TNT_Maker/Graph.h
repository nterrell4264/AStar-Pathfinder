#pragma once
#include <vector>
#include "Vertex.h"
using namespace std;
class Graph
{
public:
	Graph(int*** maze, int width, int height);
	~Graph();

	Vertex*** matrix;
	int*** mazeP; //Maze pointer
	int* start;
	int* end;

	vector<Vertex*>* path;
	int pathLength = 0;

	int currentPathIndex = 0;

	bool CalculatePath(int x, int y);
};

