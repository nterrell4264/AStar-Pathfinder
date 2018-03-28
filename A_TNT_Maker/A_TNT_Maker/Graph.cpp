#include "stdafx.h"
#include "Graph.h"

Graph::Graph()
{
	start = new int[2];
	end = new int[2];
}

Graph::~Graph()
{
	delete[] start;
	delete[] end;
	delete[] path;
}

void Graph::CalculatePath(int x, int y)
{
	if (x == **end && y == *(*end + 1)) return; //Reached end

}


