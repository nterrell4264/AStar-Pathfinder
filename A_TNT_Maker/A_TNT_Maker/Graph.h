#pragma once
#include <vector>
#include "Vertex.h"
using namespace std;
class Graph
{
public:
	Graph(int*** maze, int width, int height);
	~Graph();

	Vertex*** matrix = nullptr;
	int*** mazeP = nullptr; //Maze pointer
	int* start = nullptr;
	int* end = nullptr;

	vector<Vertex*>* path = nullptr;
	int pathLength = 0;

	int currentPathIndex = 0;

	bool CalculatePath(int x, int y);
};

