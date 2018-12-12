#include "Main.h"

///Based on the tutorial made in ATLAS.

int main() {
	#pragma region GL Stuff
	//Initializes the GLFW
	if (glfwInit() == GLFW_FALSE)
	{
		std::cout << "GLFW failed to initialize" << std::endl;
		std::cin.get();
		_CrtDumpMemoryLeaks();
		return 1;
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	//GLFW creation
	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Moveable Camera", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
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
		std::cout << "Failed to initialize GLEW" << std::endl;
		glfwTerminate();
		std::cin.get();
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

	Shape* box = new Shape();
	box->SetVertices(12, rectVertices);
	box->InitializeGL(shaderProgram);

	//Balls
	balls = new Shape*[ballCount]();
	balls[0] = MakeSphere(0.f, 0.f, 0.f, .5f, shaderProgram);
	/*for(int i = 1; i < ballCount; i++)
		balls[i] = MakeSphere(rand() % 11 - 5, rand() % 7 - 3, rand() % 11 - 5, .5f, shaderProgram);*/
	#pragma endregion

	#pragma region Draw loop
	while (!glfwWindowShouldClose(window))//Draw loop
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

		//Lock camera onto the main shape
		mainCamera->position = balls[0]->position + glm::vec3(0.0, mainCamera->position.y, 0.0);

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

		//Camera input/recalculation
		mainCamera->Update();

		//Clears the buffer
		glClear(GL_COLOR_BUFFER_BIT);
		glClearColor(.25f, 0.7f, 0.6f, 1.0f);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		box->Render();
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

		//Mesh function
		/*for (int i = 0; i < 8; i++) {
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
	Shape* ball = new Shape(originX, originY, originZ);
	//if (ballMesh == nullptr) { //Creates one mesh (pun not intended) for all balls
	const int vertexCount = (parts / 2 - 1) * parts * 18;
	GLfloat ballVertices[vertexCount];
	for (int j = 0; j < parts; j++) { //Triangles connecting to top vertex
		//Vertex 1: top
		ballVertices[j * 9] = originX;
		ballVertices[j * 9 + 1] = originY + radius;
		ballVertices[j * 9 + 2] = originZ;
		//Vertex 2: current point on next circle
		ballVertices[j * 9 + 3] = originX + cos((PI / 2) * (1 - (4.f / parts))) * (cos(j * 2 * PI / parts)) * radius;
		ballVertices[j * 9 + 4] = originY + sin((PI / 2) * (1 - (4.f / parts))) * radius;
		ballVertices[j * 9 + 5] = originZ + cos((PI / 2) * (1 - (4.f / parts))) * (sin(j * 2 * PI / parts)) * radius;
		//Vertex 3: next point on next circle
		ballVertices[j * 9 + 6] = originX + cos((PI / 2) * (1 - (4.f / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
		ballVertices[j * 9 + 7] = originY + sin((PI / 2) * (1 - (4.f / parts))) * radius;
		ballVertices[j * 9 + 8] = originZ + cos((PI / 2) * (1 - (4.f / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
	}
	for (int j = 0; j < parts; j++) { //Triangles connecting to bottom vertex
		//Vertex 1: bottom
		ballVertices[(parts + j) * 9] = originX;
		ballVertices[(parts + j) * 9 + 1] = originY - radius;
		ballVertices[(parts + j) * 9 + 2] = originZ;
		//Vertex 2: current point on next circle
		ballVertices[(parts + j) * 9 + 3] = originX + cos((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * (cos(j * 2 * PI / parts)) * radius;
		ballVertices[(parts + j) * 9 + 4] = originY + sin((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * radius;
		ballVertices[(parts + j) * 9 + 5] = originZ + cos((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * (sin(j * 2 * PI / parts)) * radius;
		//Vertex 3: next point on next circle
		ballVertices[(parts + j) * 9 + 6] = originX + cos((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
		ballVertices[(parts + j) * 9 + 7] = originY + sin((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * radius;
		ballVertices[(parts + j) * 9 + 8] = originZ + cos((PI / 2) * (1 - ((parts / 2.f - 1) * 4 / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
	}
	for (int i = 1; i < parts / 2 - 1; i++) { //Intermediary bands
		for (int j = 0; j < parts; j++) {
			//Triangle between two faces on current angle and one on next angle.
			//Vertex 1: current point
			ballVertices[(i * parts + j) * 18] = originX + cos((PI / 2) * (1 - (i * 4.f / parts))) * (cos(j * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 1] = originY + sin((PI / 2) * (1 - (i * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 2] = originZ + cos((PI / 2) * (1 - (i * 4.f / parts))) * (sin(j * 2 * PI / parts)) * radius;
			//Vertex 2: equivalent point on next circle
			ballVertices[(i * parts + j) * 18 + 3] = originX + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (cos(j * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 4] = originY + sin((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 5] = originZ + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (sin(j * 2 * PI / parts)) * radius;
			//Vertex 3: next point on next circle
			ballVertices[(i * parts + j) * 18 + 6] = originX + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 7] = originY + sin((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 8] = originZ + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
			//Triangle between two faces on current angle and one on next angle.
			//Vertex 1: current point
			ballVertices[(i * parts + j) * 18 + 9] = originX + cos((PI / 2) * (1 - (i * 4.f / parts))) * (cos(j * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 10] = originY + sin((PI / 2) * (1 - (i * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 11] = originZ + cos((PI / 2) * (1 - (i * 4.f / parts))) * (sin(j * 2 * PI / parts)) * radius;
			//Vertex 2: next point on this circle
			ballVertices[(i * parts + j) * 18 + 12] = originX + cos((PI / 2) * (1 - (i * 4.f / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 13] = originY + sin((PI / 2) * (1 - (i * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 14] = originZ + cos((PI / 2) * (1 - (i * 4.f / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
			//Vertex 3: next point on next circle
			ballVertices[(i * parts + j) * 18 + 15] = originX + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (cos((j + 1) * 2 * PI / parts)) * radius;
			ballVertices[(i * parts + j) * 18 + 16] = originY + sin((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * radius;
			ballVertices[(i * parts + j) * 18 + 17] = originZ + cos((PI / 2) * (1 - ((i + 1) * 4.f / parts))) * (sin((j + 1) * 2 * PI / parts)) * radius;
		}
	}
	ball->SetVertices(vertexCount / 9, ballVertices);
	ball->InitializeGL(shader);
	//}
	return ball;
}

void mouseWrapper(GLFWwindow * window, double xpos, double ypos)
{
	if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) mainCamera->mouseMove(xpos, ypos);
}
