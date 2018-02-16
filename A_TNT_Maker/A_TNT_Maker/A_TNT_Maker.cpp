#include "stdafx.h"

#pragma region Variables
char team[] = "A T&T Maker, made by Aiden Thinn and Nathan Terrell. AT NT.";

//Pathfinding variables

//Currently unused until A* is implemented
/*int path[][2];
int pathLength = 0;
int* end;*/
int currentPathIndex = 0;

//Temporary path
int tempPath[10][2] = { { 0, 0 }, { 1, 0 }, { 2, 0 }, { 2, 1 }, { 3, 1 }, { 3, 2 }, { 3, 3 }, { 4, 3 }, { 4, 4 }, { 4, 5 } };
int tempPathLength = 10;

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

_declspec(dllexport) void GetNextPosition(int& xpos, int& ypos) {
	xpos = **(tempPath + currentPathIndex); //Array -> Position -> First int (x)
	ypos = *(*(tempPath + currentPathIndex) + 1); //Array -> Position -> Second int (y)
	if (currentPathIndex < tempPathLength - 1) currentPathIndex++;
}

_declspec(dllexport) void SetStart(int xpos, int ypos) {
	**tempPath = xpos; //Array -> First position -> First int (x) 
	*(*tempPath + 1) = ypos; //Array -> First position -> Second int (y) 
}
_declspec(dllexport) void GetStart(int& xpos, int& ypos) {
	if (tempPath != nullptr) {
		xpos = **tempPath; //Array -> First position -> First int (x) 
		ypos = *(*tempPath + 1); //Array -> First position -> Second int (y)
	}
	else {
		xpos = -1;
		ypos = -1;
	}
}
_declspec(dllexport) void SetEnd(int xpos, int ypos) {
	 tempPath[sizeof tempPath / sizeof *tempPath - 1][0] = xpos; //Array -> Last position -> First int (x)
	 tempPath[sizeof tempPath / sizeof *tempPath - 1][1] = ypos; //Array -> Last position -> Second int (y)
}
_declspec(dllexport) void GetEnd(int& xpos, int& ypos) {
	if (tempPath != nullptr) {
		xpos = tempPath[sizeof tempPath / sizeof *tempPath - 1][0]; //Array -> Last position -> First int (x)
		ypos = tempPath[sizeof tempPath / sizeof *tempPath - 1][1]; //Array -> Last position -> Second int (y)
	}
	else //If both are not set, return -1
	{
		xpos = -1;
		ypos = -1;
	}
}
#pragma endregion