#pragma once
class Vertex
{
public:
	Vertex(int x, int y, bool canRight, bool canUp, bool canLeft, bool canDown);
	~Vertex();

	//Variables
	int xPos;
	int yPos;
	int startDis; //Distance from start
	int endDis; //Distance from end
	bool* adjacencies;
	bool visited;
};

