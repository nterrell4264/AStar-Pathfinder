#pragma once
class Vertex
{
public:
	Vertex(int x, int y);
	~Vertex();

	//Variables
	int xPos;
	int yPos;
	int startDis; //Distance from start
	int endDis; //Distance from end
	bool* adjacencies;
	bool visited;

	//Functions
	void AddAdjacency(int dir);
};

