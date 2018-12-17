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

	#pragma region Shapes
	//Unfilled rectangle for the balls
	GLfloat rectVertices[] = {
		-bounds.x,-bounds.y,-bounds.z, // triangle 1 : begin
		-bounds.x,-bounds.y, bounds.z,
		-bounds.x, bounds.y, bounds.z, // triangle 1 : end
		bounds.x, bounds.y,-bounds.z, // triangle 2 : begin
		-bounds.x,-bounds.y,-bounds.z,
		-bounds.x, bounds.y,-bounds.z, // triangle 2 : end
		bounds.x,-bounds.y, bounds.z,
		-bounds.x,-bounds.y,-bounds.z,
		bounds.x,-bounds.y,-bounds.z,
		bounds.x, bounds.y,-bounds.z,
		bounds.x,-bounds.y,-bounds.z,
		-bounds.x,-bounds.y,-bounds.z,
		-bounds.x,-bounds.y,-bounds.z,
		-bounds.x, bounds.y, bounds.z,
		-bounds.x, bounds.y,-bounds.z,
		bounds.x,-bounds.y, bounds.z,
		-bounds.x,-bounds.y, bounds.z,
		-bounds.x,-bounds.y,-bounds.z,
		-bounds.x, bounds.y, bounds.z,
		-bounds.x,-bounds.y, bounds.z,
		bounds.x,-bounds.y, bounds.z,
		bounds.x, bounds.y, bounds.z,
		bounds.x,-bounds.y,-bounds.z,
		bounds.x, bounds.y,-bounds.z,
		bounds.x,-bounds.y,-bounds.z,
		bounds.x, bounds.y, bounds.z,
		bounds.x,-bounds.y, bounds.z,
		bounds.x, bounds.y, bounds.z,
		bounds.x, bounds.y,-bounds.z,
		-bounds.x, bounds.y,-bounds.z,
		bounds.x, bounds.y, bounds.z,
		-bounds.x, bounds.y,-bounds.z,
		-bounds.x, bounds.y, bounds.z,
		bounds.x, bounds.y, bounds.z,
		-bounds.x, bounds.y, bounds.z,
		bounds.x,-bounds.y, bounds.z
	};

	Shape* box = new Shape(false);
	box->SetVertices(12, rectVertices);
	box->InitializeGL(shaderProgram);

	//Balls
	area = new Octree(vec3(0), bounds);
	for(int k = 0; k < 2; k++) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				area->AddBall(MakeSphere(-4 + 2 * i, k, -4 + 2 * j, .5f, shaderProgram));
			}
		}
	}
	//balls = new Shape*[ballCount]();
	playerBall = MakeSphere(0.f, 3.f, 0.f, .5f, shaderProgram);
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

		//Registering user's keyboard input
		Input::GetInstance()->Init(window);

		if (glfwGetKey(window, GLFW_KEY_ENTER) == GLFW_PRESS)
		{
			//Start the application
			//Gives player control over the character
		}

		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{
			//Pause the application
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

		//Updates scene
		//balls[0]->Update();
		area->Update();

		//Lock camera onto the main shape
		mainCamera->position = playerBall->position + glm::vec3(0.0, mainCamera->position.y, 0.0);
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
		//balls[0]->Render();
		area->Render();

		//'clear' for next draw call
		//glDisableVertexAttribArray(attribIndex);
		glBindVertexArray(0);
		glUseProgram(0);

		glfwSwapBuffers(window);
	}

	//Cleanup
	glfwTerminate();

	//delete[] balls;
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

Ball* MakeSphere(float originX, float originY, float originZ, float radius, GLuint shader) {
	Ball* ball = new Ball(true, radius, 1.f, originX, originY, originZ);
	ball->InitializeGL(shader);
	return ball;
}

void mouseWrapper(GLFWwindow * window, double xpos, double ypos)
{
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) mainCamera->mouseMove(xpos, ypos);
}
