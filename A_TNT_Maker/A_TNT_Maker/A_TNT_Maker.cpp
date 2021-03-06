#include "stdafx.h"
#include "Graph.h"

#pragma region Variables
char team[] = "A T&T Maker, made by Aiden Thinn and Nathan Terrell. AT NT.";

//Pathfinding variables
Graph* graph;

//Maze variables
int** maze;
bool setStart = 0;
bool setEnd = 0;
#pragma endregion

#pragma region Methods

//GetTeam Method - Returns the team's name
extern "C" _declspec(dllexport) char* GetTeam() {

	return team;
}

//SetMaze method - Initialize and set up wthe maze

extern "C" _declspec(dllexport) bool SetMaze(const int** data, int width, int height) {

	if (maze != nullptr) //Clears previous data
	{
		delete[] maze;
		delete[] graph;
	}

	if (width > 0 && height > 0) //Width and height must be valid positive sizes
	{
		maze = new int*[width]; //Initialize maze

		for (int x = 0; x < width; x++) //Loop to fill in the maze array
		{
			maze[x] = new int[height]; //Initialize maze
			for (int y = 0; y < height; y++)
			{
				maze[x][y] = data[x][y];
			}
		}
		//Creates graph
		graph = new Graph(&maze, width, height);
		(*graph).mWidth = width;
		(*graph).mHeight = height;
		return true;
	}
	else return false;
}

//GetMaze method - Set the maze's data and return the saved maze with data

extern "C" _declspec(dllexport) int** GetMaze(int& width, int& height) {

	width = (*graph).mWidth; //Get width
	height = (*graph).mHeight; //Get height

	if (maze == NULL) //If the maze data is not set
	{
		return nullptr; //Return nullptr
	}

	return maze; //Return the saved maze with data
}

//GetNextPosition method - Calculate the path, returns the next position

extern "C" _declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos) {
	if (graph == nullptr || !setStart || !setEnd) return false; //Doesn't calculate path if there isn't a graph, start, or end since it needs those.
	if((*graph).pathLength == 0) graph->BuildPath();
	if ((*graph).currentPathIndex < (*graph).finalPathLength - 1) {
		(*graph).currentPathIndex++;
		xpos = *((*graph).finalPath)[(*graph).currentPathIndex]; //Array -> Position -> First int (x)
		ypos = *(((*graph).finalPath)[(*graph).currentPathIndex] + 1); //Array -> Position -> Second int (y)
		return true;
	}
	else return false;
}

//SetStart method - Set the starting position

extern "C" _declspec(dllexport) bool SetStart(int xpos, int ypos) {

	if ((xpos >= 0 && ypos >= 0) && (xpos < (*graph).mWidth && ypos < (*graph).mHeight))
	{
		*(*graph).start = xpos; //Array -> First int (x) 
		*((*graph).start + 1) = ypos; //Array -> Second int (y)
		setStart = true;
		return true;
	}
	else return false;
}

//GetStart method - Get the saved starting position

extern "C" _declspec(dllexport) bool GetStart(int& xpos, int& ypos) {

	if (setStart) {
		xpos = *(*graph).start; //Array -> First position -> First int (x) 
		ypos = *((*graph).start + 1); //Array -> First position -> Second int (y)
		return true;
	}
	else return false;
}

//SetEnd method - Set the ending position

extern "C" _declspec(dllexport) bool SetEnd(int xpos, int ypos) {

	if ((xpos >= 0 && ypos >= 0) && (xpos < (*graph).mWidth && ypos < (*graph).mHeight))
	{
		*(*graph).end = xpos; //Array -> First int (x) 
		*((*graph).end + 1) = ypos; //Array -> Second int (y)
		setEnd = true;
		return true;
	}
	else return false;
}

//GetEnd method - Get the saved ending position

extern "C" _declspec(dllexport) bool GetEnd(int& xpos, int& ypos) {

	if (setEnd) {
		xpos = *(*graph).end; //Array -> First position -> First int (x) 
		ypos = *((*graph).end + 1); //Array -> First position -> Second int (y)
		return true;
	}
	else return false;
}

//Restart method - Player starts back at the starting position, and step through to the end again

extern "C" _declspec(dllexport) bool Restart() {
	(*graph).currentPathIndex = 0;
	return true;
}
#pragma endregion