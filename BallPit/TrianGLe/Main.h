#pragma once
#include "Include.h"

//Window data
const GLint WIDTH = 800, HEIGHT = 600;
GLuint colorbuffer;

//Cameras
Camera** cameras;
Camera* mainCamera;
int camIndex = 0;
bool camKeyPressed = false;

//Shape stuff
Shape** balls;
//Mesh* ballMesh = nullptr;
const int ballCount = 10;
const int parts = 16;

Shape* MakeSphere(float originX, float originY, float originZ, float radius, GLuint shader);

void mouseWrapper(GLFWwindow* window, double xpos, double ypos);