#include "stdafx.h"
#include <algorithm>
#include "Graph.h"
using namespace std;

Graph::Graph(int*** maze, int width, int height)
{
	//Initializes variables
	start = new int[2];
	end = new int[2];
	//Defines graph
	mazeP = maze;
	matrix = new Vertex**[width];
		for (int x = 0; x < width; x++) { //Creates and populates rows
			matrix[x] = new Vertex*[height];
			for (int y = 0; y < height; y++) { //Creates and populates cells in the row
				Vertex* vertex = new Vertex(x, y);
				if ((*maze)[x][y] != 0) { //Doesn't bother adding info to walls
					//Checks for open neighbors for pathfinding
					if (x < width - 1 && (*maze)[x + 1][y] != 0) vertex->AddAdjacency(0);
					if (y > 0 && (*maze)[x][y - 1] != 0) vertex->AddAdjacency(1);
					if (x > 0 && (*maze)[x - 1][y] != 0) vertex->AddAdjacency(2);
					if (y < height - 1 && (*maze)[x][y + 1] != 0) vertex->AddAdjacency(3);
				}
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

void Graph::BuildPath() {
	//Sets heuristics values
	for (int x = 0; x < mWidth; x++) {
		for (int y = 0; y < mHeight; y++) {
			Vertex* vertex = matrix[x][y];
			vertex->heuristic = pathLength + abs(x - *end) + abs(y - *(end + 1)) + (*mazeP)[x][y] - 1; //Distance along path + distance from end + move weight of space
		}
	}
	//Starts pathfinding
	CalculatePath(*start, *(start + 1));
}

int Graph::CalculatePath(int x, int y)
{
	Vertex* vertex = matrix[x][y];
	if ((*mazeP)[x][y] == 0 || (*vertex).visited) return INT_MAX;
	//Add vertex to path
	(*path).push_back(vertex);
	pathLength++;
	if (x == *end && y == *(end + 1)) {
		SetShortestPath();
		(*path).pop_back();
		pathLength--;
		return pathLength; //Reached end
	}
	(*vertex).visited = true;
	//Recursively finds next step, in order of distance from the endpoint
	int curPath = INT_MAX;
	int shortPath = INT_MAX;
	for (Vertex* neighbor : AdjacencyDistances(vertex)) {
		curPath = CalculatePath((*neighbor).xPos, (*neighbor).yPos);
		if (curPath < shortPath) shortPath = curPath;
	}
	//Removes vertex from path once we're done with it
	(*path).pop_back();
	pathLength--;
	return shortPath;
}

vector<Vertex*> Graph::AdjacencyDistances(Vertex* vertex) {
	vector<Vertex*> neighbors(0);
	//Finds valid neighbors
	if (*((*vertex).adjacencies)) { //Right
		neighbors.push_back(matrix[(*vertex).xPos + 1][(*vertex).yPos]);
	}
	if (*((*vertex).adjacencies + 1)) { //Up
		neighbors.push_back(matrix[(*vertex).xPos][(*vertex).yPos - 1]);
	}
	if (*((*vertex).adjacencies + 2)) { //Left
		neighbors.push_back(matrix[(*vertex).xPos - 1][(*vertex).yPos]);
	}
	if (*((*vertex).adjacencies + 3)) { //Down
		neighbors.push_back(matrix[(*vertex).xPos][(*vertex).yPos + 1]);
	}
	sort(neighbors.begin(), neighbors.end(), sortDis); //Sorts list in ascending order by heuristics value
	return neighbors;
}

bool sortDis(const Vertex* a, const Vertex* b) {
	return (*a).heuristic < (*b).heuristic;
}

void Graph::SetShortestPath()
{
	if (pathLength > finalPathLength)
	{
		return;
	}

	if (finalPath != nullptr) //Deletes previous shortest path if it exists
	{
		delete[] finalPath;
	}
	//Creates and populates array with coordinates of path's vertices
	finalPathLength = pathLength;
	finalPath = new int*[finalPathLength];
	for (int i = 0; i < pathLength; i++) {
		finalPath[i] = new int[2];
		*finalPath[i] = (*path)[i]->xPos; //X
		*(finalPath[i]+1) = (*path)[i]->yPos; //Y
	}
}