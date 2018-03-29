#include "stdafx.h"
#include "Vertex.h"

Vertex::Vertex(int x, int y) {
	xPos = x;
	yPos = y;
	adjacencies = new bool[4]{ false, false, false, false };
}

Vertex::~Vertex()
{
	delete[] adjacencies;
}

void Vertex::AddAdjacency(int dir) {
	adjacencies[dir] = true;
}
