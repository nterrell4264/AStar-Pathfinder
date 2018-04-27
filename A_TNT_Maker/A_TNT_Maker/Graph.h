#pragma once
#include <vector>
#include "Vertex.h"
using namespace std;
class Graph
{
public:
	Graph(int*** maze, int width, int height);
	~Graph();

	//Vertex graph for pathfinding
	Vertex*** matrix = nullptr;
	int* start = nullptr;
	int* end = nullptr;
	//Original maze for reference
	int*** mazeP = nullptr; //Maze pointer
	int mWidth = 0;
	int mHeight = 0;

	vector<Vertex*>* path = nullptr;
	int pathLength = 0;
	int** finalPath = nullptr;
	int finalPathLength = INT_MAX;

	int currentPathIndex = 0;

	void BuildPath(); //Initializes pathfinding
private:
	int CalculatePath(int x, int y); //Recursive pathfinding function
	vector<Vertex*> AdjacencyDistances(Vertex* vertex); //Returns a sorted list of a vertex's neighbors using the distance heuristic
	void SetShortestPath();
};

bool sortDis(const Vertex* a, const Vertex* b); //Function that compares two heuristic values to find the lowest