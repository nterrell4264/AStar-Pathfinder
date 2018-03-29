#include "stdafx.h"
#include "Graph.h"

#pragma region Variables
char team[] = "A T&T Maker, made by Aiden Thinn and Nathan Terrell. AT NT.";

//Pathfinding variables
Graph graph;

//Maze variables
int** maze;
int mWidth;
int mHeight;
#pragma endregion

#pragma region Methods
_declspec(dllexport) char* GetTeam() {
	return team;
}

_declspec(dllexport) void SetMaze(const int** data, int width, int height) {

	if (maze != nullptr) //Clears previous data
	{
		delete[] maze;
	}

	maze = new int*[width]; //Initialize maze

	mWidth = width; //Set width
	mHeight = height; //Set height

	for (int x = 0; x < width; x++) //Loop to fill in the maze array
	{
		maze[x] = new int[height]; //Initialize maze

		for (int y = 0; y < height; y++)
		{
			 maze[x][y] = data[x][y];
		}
	}
}
_declspec(dllexport) int** GetMaze(int& width, int& height) {
	width = mWidth; //Get width
	height = mHeight; //Get height
	return maze; //Return the saved maze with data
}

_declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos) {
	xpos = (*(*graph.path)[graph.currentPathIndex]).xPos; //Array -> Position -> First int (x)
	ypos = (*(*graph.path)[graph.currentPathIndex]).yPos; //Array -> Position -> Second int (y)
	if (graph.currentPathIndex < graph.pathLength - 1) {
		graph.currentPathIndex++;
		return true;
	}
	else return false;
}

_declspec(dllexport) bool SetStart(int xpos, int ypos) {
	*graph.start = xpos; //Array -> First int (x) 
	*(graph.start+1) = ypos; //Array -> Second int (y)
	return true;
}
_declspec(dllexport) bool GetStart(int& xpos, int& ypos) {
	if (graph.start != nullptr) {
		xpos = *graph.start; //Array -> First position -> First int (x) 
		ypos = *(graph.start + 1); //Array -> First position -> Second int (y)
		return true;
	}
	else return false;
}
_declspec(dllexport) bool SetEnd(int xpos, int ypos) {
	*graph.end = xpos; //Array -> First int (x) 
	*(graph.end + 1) = ypos; //Array -> Second int (y)
	return true;
}
_declspec(dllexport) bool GetEnd(int& xpos, int& ypos) {
	if (graph.end != nullptr) {
		xpos = *graph.end; //Array -> First position -> First int (x) 
		ypos = *(graph.end + 1); //Array -> First position -> Second int (y)
		return true;
	}
	else {
		xpos = -1;
		ypos = -1;
		return false;
	}
}

_declspec(dllexport) bool Restart() {
	graph.currentPathIndex = 0;
}
#pragma endregion