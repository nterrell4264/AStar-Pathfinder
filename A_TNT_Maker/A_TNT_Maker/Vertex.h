#pragma once
class Vertex
{
public:
	Vertex(int x, int y);
	~Vertex();

	//Variables
	int xPos;
	int yPos;
	int heuristic; //A number that determines how fast the tile seems to be. Lower numbers are better.
	bool* adjacencies;
	bool visited;

	//Functions
	void AddAdjacency(int dir);
};

