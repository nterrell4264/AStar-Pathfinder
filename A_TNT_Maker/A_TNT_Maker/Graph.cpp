#include "stdafx.h"
#include "Graph.h"

Graph::Graph(int*** maze, int width, int height)
{
	//Initializes variables
	start = new int[2];
	end = new int[2];
	//Defines graph
	mazeP = maze;
	matrix = new Vertex**[width];
		for (int x = 0; x < width; x++) {
			matrix[x] = new Vertex*[height];
			for (int y = 0; y < height; y++) {
				matrix[x][y] = new Vertex(x, y, (*maze)[x + 1][y] == 0, (*maze)[x][y + 1] == 0, (*maze)[x - 1][y] == 0, (*maze)[x][y - 1] == 0);
		}
	}
	path = new vector<Vertex*>[0];
}

Graph::~Graph()
{
	delete[] start;
	delete[] end;

	for (int i = 0; i < pathLength; i++) {
		delete (*path)[i];
	}
}

bool Graph::CalculatePath(int x, int y)
{
	Vertex* vertex = matrix[x][y];
	if (*mazeP[x][y] == 0 || (*vertex).visited) return false;
	if (x == *end && y == *(end + 1)) return true; //Reached end
	//Add vertex to path
	(*path).push_back(vertex);
	//Recursively finds next step
	if ((*vertex).adjacencies) {
		if (CalculatePath(x + 1, y)) return true;
	}
	if (*((*vertex).adjacencies + 1)) {
		if (CalculatePath(x, y + 1)) return true;
	}
	if (*((*vertex).adjacencies + 2)) {
		if (CalculatePath(x - 1, y)) return true;
	}
	if (*((*vertex).adjacencies + 3)) {
		if (CalculatePath(x, y - 1)) return true;
	}
	return false;
}


