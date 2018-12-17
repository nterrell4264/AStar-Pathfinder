#include "Input.h"

//for singleton
Input* Input::instance = nullptr;

Input::Input()
{
}

Input::~Input()
{
}

Input* Input::GetInstance()
{
	if (instance == nullptr)
	{
		instance = new Input();
	}
	return instance;
}

void Input::Release()
{
	delete instance;
	instance = nullptr;
}

void Input::Init(GLFWwindow * window)
{
	this->window = window;
}

bool Input::IsKeyDown(int key)
{
	return glfwGetKey(window, key) == GLFW_PRESS;
}
