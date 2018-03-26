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

void Graph::CalculatePath() {

}
