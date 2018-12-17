#include "Main.h"

///Based on the tutorial made in ATLAS.

int main() {
	#pragma region GL Stuff
	//Initializes the GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		cout << "GLFW failed to initialize" << endl;
		cin.get();
		_CrtDumpMemoryLeaks();
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//GLFW creation
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Moveable Camera", nullptr, nullptr);
	if (window == nullptr)
	{
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();
		return EXIT_FAILURE;
	}
	glfwMakeContextCurrent(window);
	glViewport(0, 0, WIDTH, HEIGHT);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwSetCursorPosCallback(window, &mouseWrapper);

	//GLEW
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW" << endl;
		glfwTerminate();
		cin.get();
		_CrtDumpMemoryLeaks();
		return EXIT_FAILURE;
	}

	///Shaders
	GLuint shaderProgram = glCreateProgram();
	//Vertex Shader
	Shader *vs = new Shader();
	vs->InitFromFile("shaders/vertexShader.glsl", GL_VERTEX_SHADER);
	glAttachShader(shaderProgram, vs->GetShaderLoc());
	//Fragment Shader
	Shader *fs = new Shader();
	fs->InitFromFile("shaders/fragmentShader.glsl", GL_FRAGMENT_SHADER);
	glAttachShader(shaderProgram, fs->GetShaderLoc());

	glLinkProgram(shaderProgram);

	//Cameras
	cameras = new Camera*[3];
	cameras[0] = new Camera(&shaderProgram, window);
	cameras[1] = new Camera(&shaderProgram, window, vec3(10.f,5.f,0.f));
	cameras[2] = new Camera(&shaderProgram, window, vec3(0.f,-5.f,0.f));
	mainCamera = cameras[0];
	#pragma endregion

	// Pause Screen variable
	bool paused = false;

	#pragma region Shapes
	//Unfilled rectangle for the balls
	GLfloat rectVertices[] = {
		-1.0f,-1.0f,-1.0f, // triangle 1 : begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f, // triangle 1 : end
		1.0f, 1.0f,-1.0f, // triangle 2 : begin
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f, // triangle 2 : end
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f
	};

	Shape* box = new Shape(false);
	box->SetVertices(12, rectVertices);
	box->InitializeGL(shaderProgram);

	//Balls
	balls = new Shape*[ballCount]();
	balls[0] = MakeSphere(0.f, 0.f, 0.f, .5f, shaderProgram);
	/*for(int i = 1; i < ballCount; i++)
		balls[i] = MakeSphere(rand() % 11 - 5, rand() % 7 - 3, rand() % 11 - 5, .5f, shaderProgram);*/
	#pragma endregion

	#pragma region Draw loop
	while (!glfwWindowShouldClose(window))
	{
		//General input
		glfwPollEvents();
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) break; //Exit command
		if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) { //Switch cameras
			if (!camKeyPressed) {
				camIndex = (camIndex + 1) % 3;
				mainCamera = cameras[camIndex];
			}
			camKeyPressed = true;
		}
		else {
			camKeyPressed = false;
		}

		//Registering user's keyboard inputs
		Input::GetInstance()->Init(window);
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			//Pause the application
			paused = !paused;
		}

		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			//Reset the application
			//glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
		}

		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			//Quit the application
			exit(0);
		}

		// Player's character movement inputs
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) balls[0]->position +=
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) balls[0]->position -= 
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) balls[0]->position += 
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) balls[0]->position -= 
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) balls[0]->position -= 
		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) balls[0]->position += 

		//Updates scene
		balls[0]->Update();

		//Lock camera onto the main shape
		mainCamera->position = balls[0]->position + glm::vec3(1.0, mainCamera->position.y, 0.0);
		//Camera input/recalculation
		mainCamera->Update();

		//Clears the buffer
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(.25f, 0.7f, 0.6f, 1.0f);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		box->Render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Mesh function
		/*for (int i = 0; i < ballCount; i++) {
			balls[i]->Render();
		}*/
		balls[0]->Render();

		//'clear' for next draw call
		//glDisableVertexAttribArray(attribIndex);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}

	//Cleanup
	glfwTerminate();

	delete[] balls;
	//delete ballMesh;

	delete box;

	delete[] cameras;
	mainCamera = nullptr;

	delete vs;
	delete fs;
	_CrtDumpMemoryLeaks();

	return EXIT_SUCCESS;
	#pragma endregion
}

Shape* MakeSphere(float originX, float originY, float originZ, float radius, GLuint shader) {
	Ball* ball = new Ball(true, radius, 1.f, originX, originY, originZ);
	//if (ballMesh == nullptr) { //Creates one mesh (pun not intended) for all balls
	const int vertexCount = (parts / 2 - 1) * parts * 18;
	GLfloat ballVertices[vertexCount];
	ball->InitializeGL(shader);
	//}
	return ball;
}

void mouseWrapper(GLFWwindow * window, double xpos, double ypos)
{
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) mainCamera->mouseMove(xpos, ypos);
}
