#pragma once
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace glm;

#include <vector>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
using namespace std;

//Audio
#include <irrKlang.h>
using namespace irrklang;

//Global variables
const float PI = 3.14159f;
const float friction = .03f; //Frictional force reduction coefficient

const int parts = 16; //Subdivisions of circular models
const vec3 bounds = vec3(5.f,5.f,5.f); //Outer bounds of ballpit