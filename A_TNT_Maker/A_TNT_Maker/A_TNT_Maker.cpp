#include "stdafx.h"
#include "Graph.h"

#pragma region Variables
char team[] = "A T&T Maker, made by Aiden Thinn and Nathan Terrell. AT NT.";

//Pathfinding variables
Graph* graph;

//Maze variables
int** maze;
int mWidth;
int mHeight;
bool setStart = 0;
bool setEnd = 0;
#pragma endregion

#pragma region Methods

//GetTeam Method - Returns the team's name
_declspec(dllexport) char* GetTeam() {

	return team;
}

//SetMaze method - Initialize and set up wthe maze
_declspec(dllexport) bool SetMaze(const int** data, int width, int height) {

	if (maze != nullptr) //Clears previous data
	{
		delete[] maze;
		delete[] graph;
	}

	if ((width != 0 && height != 0) && (width > 0 && height > 0)) //If width is not 0 or negative and height is not 0 or negative
	{
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
		graph = new Graph(&maze, mWidth, mHeight);
		return true;
	}
	else return false;
}

//GetMaze method - Set the maze's data and return the saved maze with data
_declspec(dllexport) int** GetMaze(int& width, int& height) {

	width = mWidth; //Get width
	height = mHeight; //Get height

	if (maze == NULL) //If the maze data is not set
	{
		return nullptr; //Return nullptr
	}

	return maze; //Return the saved maze with data
}

//GetNextPosition method - Calculate the path, returns the next position
_declspec(dllexport) bool GetNextPosition(int& xpos, int& ypos) {

	if((*graph).path == nullptr) graph->CalculatePath(*(*graph).start, *((*graph).start + 1));

	xpos = (*(*(*graph).path)[(*graph).currentPathIndex]).xPos; //Array -> Position -> First int (x)
	ypos = (*(*(*graph).path)[(*graph).currentPathIndex]).yPos; //Array -> Position -> Second int (y)

	if ((*graph).currentPathIndex < (*graph).pathLength - 1) {
		(*graph).currentPathIndex++;
		return true;
	}
	else return false;
}

//SetStart method - Set the starting position
_declspec(dllexport) bool SetStart(int xpos, int ypos) {

	if ((xpos > 0 && ypos > 0) && (xpos < mWidth && ypos < mHeight))
	{
		*(*graph).start = xpos; //Array -> First int (x) 
		*((*graph).start + 1) = ypos; //Array -> Second int (y)
		setStart = true;
		return true;
	}
	else return false;
}

//GetStart method - Get the saved starting position
_declspec(dllexport) bool GetStart(int& xpos, int& ypos) {

	if (setStart) {
		xpos = *(*graph).start; //Array -> First position -> First int (x) 
		ypos = *((*graph).start + 1); //Array -> First position -> Second int (y)
		return true;
	}
	else return false;
}

//SetEnd method - Set the ending position
_declspec(dllexport) bool SetEnd(int xpos, int ypos) {

	if ((xpos > 0 && ypos > 0) && (xpos < mWidth && ypos < mHeight))
	{
		*(*graph).end = xpos; //Array -> First int (x) 
		*((*graph).end + 1) = ypos; //Array -> Second int (y)
		setEnd = true;
		return true;
	}
	else return false;
}

//GetEnd method - Get the saved ending position
_declspec(dllexport) bool GetEnd(int& xpos, int& ypos) {

	if (setEnd) {
		xpos = *(*graph).end; //Array -> First position -> First int (x) 
		ypos = *((*graph).end + 1); //Array -> First position -> Second int (y)
		return true;
	}
	else return false;
}

//Restart method - Player starts back at the starting position, and step through to the end again
_declspec(dllexport) bool Restart() {

	(*graph).currentPathIndex = 0;
	return true;
}
#pragma endregion