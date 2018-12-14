#pragma once
#include "Include.h"

class Shape
{
public:
	Shape(bool isDynamic, float shapeMass = 1.f, float xPos = 0, float yPos = 0, float zPos = 0);
	~Shape();

	//Physics data
	bool dynamic;
	float mass;

	vector<vec3*> linForces;
	vector<vec3*> angForces;

	vec3 position;
	vec3 rotation;

	vec3 velocity;
	vec3 angVelocity;

	vec3 acceleration;
	vec3 angAccel;

	//GL variables
	GLuint vao;
	GLuint vbo;
	//Mesh variables
	//Mesh* mesh;
	GLfloat triCount = 0;
	GLfloat coordCount = 0;
	vector<GLfloat> pointData;

	//Render functions
	void Render();
	void InitializeGL(GLuint shader);
	virtual void SetVertices(GLfloat triNum, GLfloat points[]);

	//Data-related functions
	void Update();
	void ApplyForce(vec3 force, vec3 location);
	void Translate(float dx = 0.f, float dy = 0.f, float dz = 0.f);
	void Rotate(float rx = 0.f, float ry = 0.f, float rz = 0.f);
	void Reset();
};

