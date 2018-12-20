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

	//Audio
	ISoundEngine *SoundEngine = createIrrKlangDevice();

	//Cameras
	cameras = new Camera*[3];
	cameras[0] = new Camera(&shaderProgram, window, vec3(0.f, 0.f, -20.f));
	cameras[1] = new Camera(&shaderProgram, window, vec3(10.f,5.f,0.f));
	cameras[2] = new Camera(&shaderProgram, window, vec3(0.f,-5.f,0.f));
	mainCamera = cameras[0];
	#pragma endregion

	SoundEngine->play2D("../audio/background.mp3", GL_TRUE);

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
				area->AddBall(MakeSphere(2 * (i - 3), k, 2 * (j - 3), .5f, shaderProgram));
			}
		}
	}
	//balls = new Shape*[ballCount]();
	playerBall = MakeSphere(0.f, 3.f, 0.f, .5f, shaderProgram);
	/*for(int i = 1; i < ballCount; i++)
		balls[i] = MakeSphere(rand() % 11 - 5, rand() % 7 - 3, rand() % 11 - 5, .5f, shaderProgram);*/
	#pragma endregion

	cout << "BALL PIT\nby Nathan Terrell & Aiden Thinn\n\nINSTRUCTIONS\nMovement:\nW - go forward\nA - go left\nS - go backward\nD - go right\nControls:\nR - reset\nP - pause\nQ - quit" << endl;

	#pragma region Draw loop
	while (!glfwWindowShouldClose(window))
	{
		//General input
		glfwPollEvents();
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

		//Pause the application
		if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
		{ 
			Sleep(500);
			int pauseTimer = 5000;
			while (true) {
				glfwPollEvents();
				if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS && pauseTimer <= 10) {
					break;
				}
				if (pauseTimer > 0) pauseTimer--;
			}

			
		}

		//Reset the application
		if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
		{
			
		}

		//Quit the application
		if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
		{
			exit(0);
		}

		// Player's character movement inputs
		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) playerBall->position.z += .001;
		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) playerBall->position.z -= .001;
		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) playerBall->position.x -= .001;
		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) playerBall->position.x += .001;


		//Lock the camera to the player's ball
		mainCamera->position = playerBall->position -(13.0f * mainCamera->forward);

		//Updates scene
		//balls[0]->Update();
		area->Update();

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
		playerBall->Update();
		playerBall->Render();
		
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
