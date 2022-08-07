#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <GL/glew.h>
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Buffer.h"
#include "../lib/glm/gtc/matrix_transform.hpp"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

int main() {
	// init glfw
	if ( !glfwInit() ) 
	{
		std::cout << "could not initialize glfw" << std::endl;

		return -1;
	}

	// create window
	glfwWindowHint(GLFW_SAMPLES, 8);
	GLFWwindow* win = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "", nullptr, nullptr);

	if (!win) 
	{
		std::cout << "could not create opengl window" << std::endl;
		glfwTerminate();

		return -1;
	}

	glfwMakeContextCurrent(win);

    glewInit();
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glScissor(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_SCISSOR_TEST);

	Shader shader("data/vertex.glsl", "data/fragment.glsl");

	std::vector<uint16_t> indexes{ 0, 1, 2 };
    std::vector<Buffer*> bufferArray;
    std::vector<Vertex> vertexArray
    {
        Vertex(glm::vec3(0.f, 0.5f, 0.f), glm::vec3(1.f, 0.8f, 0.f)),
        Vertex(glm::vec3(-0.5f, -0.5f, 0.f), glm::vec3(0.f, 0.f, 0.f)),
        Vertex(glm::vec3(0.5f, -0.5f, 0.f), glm::vec3(0.25f, 0.1f, 0.f))
    };

    bufferArray.reserve(9);
    for (int i = 0; i < 9; ++i)
    {
        bufferArray.push_back(new Buffer(vertexArray, indexes));
    }

// *************************** Setting triangles position ******************************

    bufferArray[0]->position = glm::vec3(-3, 0, -3);
    bufferArray[1]->position = glm::vec3(-3, 0, 0);
    bufferArray[2]->position = glm::vec3(-3, 0, -6);

    bufferArray[3]->position = glm::vec3(0, 0, -3);
    bufferArray[4]->position = glm::vec3(0, 0, 0);
    bufferArray[5]->position = glm::vec3(0, 0, -6);

    bufferArray[6]->position = glm::vec3(3, 0, -3);
    bufferArray[7]->position = glm::vec3(3, 0, 0);
    bufferArray[8]->position = glm::vec3(3, 0, -6);

// ***************************************************************************************

    glm::mat4 perspective = glm::perspective(45.f, 1.3f, 0.2f, 80.f);
    glm::mat4 pointOfView = glm::lookAt(glm::vec3(0.f, 0.f, 6.f), glm::vec3(0, 0, 0), glm::vec3(0, 1.f, 0));

	// main loop
	float angle = 0;
	double lastTime = glfwGetTime();

	while ( !glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE) ) 
	{
		// get delta time
		auto deltaTime = static_cast<float>(glfwGetTime() - lastTime);
		lastTime = glfwGetTime();

		// get window size
		int screenWidth, screenHeight;
		glfwGetWindowSize(win, &screenWidth, &screenHeight);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        for (auto& bufferIterator : bufferArray)
        {
            bufferIterator->Update(deltaTime);
            bufferIterator->Draw(shader, pointOfView, perspective);
        }

		// refresh screen
		glfwSwapBuffers(win);
		glfwPollEvents();
	}

	// shutdown
	glfwTerminate();
}