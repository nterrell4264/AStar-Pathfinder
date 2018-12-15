#include "Ball.h"

Ball::Ball(bool isDynamic, float collRadius, float shapeMass, float xPos, float yPos, float zPos) : Shape(isDynamic, shapeMass, xPos, yPos, zPos)
{
	radius = collRadius;
	SetVertices();
}


Ball::~Ball()
{
}

void Ball::SetVertices() {
	const int vertexCount = (parts / 2 - 1) * parts * 18;
	GLfloat ballVertices[vertexCount];
	for (int j = 0; j < parts; j++) { //Triangles connecting to top vertex
									  //Vertex 1: top
		ballVertices[j * 9] = position.x;
		ballVertices[j * 9 + 1] = position.y + radius;
		ballVertices[j * 9 + 2] = position.z;
		//Vertex 2: current point on next circle
		ballVertices[j * 9 + 3] = position.x + cos((PI / 2) * (1 - (4.f / parts))) * (cos(j * 2 * PI / parts)) * radius;
		ballVertices[j * 9 + 4] = position.y + sin((PI / 2) * (1 - (4.f / parts))) * radius;
		ballVertices[j * 9 + 5] = position.z + cos((PI / 2) * (1 - (4.f / parts))) * (sin(j * 2 * PI / parts)) * radius;
		//Vertex 3: next point on next circle
		ballVertices[j * 9 + 6] = position.x + cos((PI / 2) * (1 - (4.f / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
		ballVertices[j * 9 + 7] = position.y + sin((PI / 2) * (1 - (4.f / parts))) * radius;
		ballVertices[j * 9 + 8] = position.z + cos((PI / 2) * (1 - (4.f / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
	}
	for (int j = 0; j < parts; j++) { //Triangles connecting to bottom vertex
									  //Vertex 1: bottom
		ballVertices[(parts + j) * 9] = position.x;
		ballVertices[(parts + j) * 9 + 1] = position.y - radius;
		ballVertices[(parts + j) * 9 + 2] = position.z;
		//Vertex 2: current point on next circle
		ballVertices[(parts + j) * 9 + 3] = position.x + cos((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * (cos(j * 2 * PI / parts)) * radius;
		ballVertices[(parts + j) * 9 + 4] = position.y + sin((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * radius;
		ballVertices[(parts + j) * 9 + 5] = position.z + cos((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * (sin(j * 2 * PI / parts)) * radius;
		//Vertex 3: next point on next circle
		ballVertices[(parts + j) * 9 + 6] = position.x + cos((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
		ballVertices[(parts + j) * 9 + 7] = position.y + sin((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * radius;
		ballVertices[(parts + j) * 9 + 8] = position.z + cos((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
	}
	for (int i = 1; i < parts / 2 - 1; i++) { //Intermediary bands
		for (int j = 0; j < parts; j++) {
			//Triangle between two faces on current angle and one on next angle.
			//Vertex 1: current point
			ballVertices[(i * parts + j) * 18] = position.x + cos((PI / 2) * (1 - (i * 4.f / parts))) * (cos(j * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 1] = position.y + sin((PI / 2) * (1 - (i * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 2] = position.z + cos((PI / 2) * (1 - (i * 4.f / parts))) * (sin(j * 2 * PI / parts)) * radius;
			//Vertex 2: equivalent point on next circle
			ballVertices[(i * parts + j) * 18 + 3] = position.x + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (cos(j * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 4] = position.y + sin((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 5] = position.z + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (sin(j * 2 * PI / parts)) * radius;
			//Vertex 3: next point on next circle
			ballVertices[(i * parts + j) * 18 + 6] = position.x + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 7] = position.y + sin((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 8] = position.z + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
			//Triangle between two faces on current angle and one on next angle.
			//Vertex 1: current point
			ballVertices[(i * parts + j) * 18 + 9] = position.x + cos((PI / 2) * (1 - (i * 4.f / parts))) * (cos(j * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 10] = position.y + sin((PI / 2) * (1 - (i * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 11] = position.z + cos((PI / 2) * (1 - (i * 4.f / parts))) * (sin(j * 2 * PI / parts)) * radius;
			//Vertex 2: next point on this circle
			ballVertices[(i * parts + j) * 18 + 12] = position.x + cos((PI / 2) * (1 - (i * 4.f / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 13] = position.y + sin((PI / 2) * (1 - (i * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 14] = position.z + cos((PI / 2) * (1 - (i * 4.f / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
			//Vertex 3: next point on next circle
			ballVertices[(i * parts + j) * 18 + 15] = position.x + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 16] = position.y + sin((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 17] = position.z + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
		}
	}
	Shape::SetVertices(vertexCount / 9, ballVertices);
}
