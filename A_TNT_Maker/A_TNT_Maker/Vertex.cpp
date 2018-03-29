#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex(int x, int y, bool canRight, bool canUp, bool canLeft, bool canDown) {
	xPos = x;
	yPos = y;
	adjacencies = new bool[4] {canRight, canUp, canLeft, canDown};
}

Vertex::~Vertex()
{
	delete[] adjacencies;
}
