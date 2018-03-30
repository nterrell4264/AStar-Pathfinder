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
				Vertex* vertex = new Vertex(x, y);
				if (x < width - 1 && (*maze)[x + 1][y] == 0) vertex->AddAdjacency(0);
				if (y < height - 1 && (*maze)[x][y + 1] == 0) vertex->AddAdjacency(1);
				if (x > 0 && (*maze)[x - 1][y] == 0) vertex->AddAdjacency(2);
				if (y > 0 && (*maze)[x][y - 1] == 0) vertex->AddAdjacency(3);
				vertex->startDis = abs(x - *start) + abs(y - *(start + 1));
				vertex->endDis = abs(x - *end) + abs(y - *(end + 1));
				matrix[x][y] = vertex;
		}
	}
	path = new vector<Vertex*>[1];
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
	if ((*mazeP)[x][y] != 0 || (*vertex).visited) return false;
	//Add vertex to path
	(*path).push_back(vertex);
	pathLength++;
	if (x == *end && y == *(end + 1)) return true; //Reached end
	(*vertex).visited = true;
	//Recursively finds next step
	if (*((*vertex).adjacencies)) {
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
	//Removes vertex from path if there is no path from it
	(*path).pop_back();
	pathLength--;
	return false;
}


