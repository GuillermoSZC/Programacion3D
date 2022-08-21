#ifdef _MSC_VER
#pragma comment(linker, "/SUBSYSTEM:windows /ENTRY:mainCRTStartup")
#endif

#include <GL/glew.h>
#include "../lib/glfw/glfw3.h"
#include <iostream>
#include <vector>
#include "Shader.h"
#include "Buffer.h"
#include "State.h"
#include "World.h"
#include "Mesh.h"
#include "Model.h"

#include "../lib/glm/gtc/matrix_transform.hpp"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768

int main() {
   // init glfw
   if (!glfwInit())
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
   glEnable(GL_DEPTH_TEST);
   glEnable(GL_SCISSOR_TEST);

   State::GetState()->defaultShader = std::make_shared<Shader>("data/vertex.glsl", "data/fragment.glsl");

   std::vector<std::shared_ptr<Model>> models;
   std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>();
   std::shared_ptr<Camera> camera = std::make_shared<Camera>(SCREEN_WIDTH, SCREEN_HEIGHT);

//              Setting colour and position of the vertices of each square side 
// TOP - DOWN
   std::vector<Vertex> topVertices
   {      
      Vertex(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 0.83f, 0.f)),
      Vertex(glm::vec3(1.f, 1.f, -1.f), glm::vec3(1.f, 0.83f, 0.f)),
      Vertex(glm::vec3(-1.f, 1.f, -1.f), glm::vec3(1.f, 0.83f, 0.f)),
      Vertex(glm::vec3(-1.f, 1.f, 1.f), glm::vec3(1.f, 0.83f, 0.f)),

      Vertex(glm::vec3(1.f, -1.f, -1.f), glm::vec3(0.f, 0.f, 0.f)),
      Vertex(glm::vec3(1.f, -1.f, 1.f), glm::vec3(0.f, 0.f, 0.f)),
      Vertex(glm::vec3(-1.f, -1.f, 1.f), glm::vec3(0.f, 0.f, 0.f)),
      Vertex(glm::vec3(-1.f, -1.f, -1.f), glm::vec3(0.f, 0.f, 0.f))
   };
// SIDES FRONT-LEFT-RIGHT-BACK
   std::vector<Vertex> sideVertices
   {
      // front
      Vertex(glm::vec3(1.f, -1.f, 1.f), glm::vec3(0.f, 0.f, 0.f)), 
      Vertex(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 0.8f, 0.f)), // top-right corner
      Vertex(glm::vec3(-1.f, 1.f, 1.f), glm::vec3(1.f, 0.8f, 0.f)), // top-left corner
      Vertex(glm::vec3(-1.f, -1.f, 1.f), glm::vec3(0.f, 0.f, 0.f)),
      // right
      Vertex(glm::vec3(1.f, -1.f, -1.f), glm::vec3(0.f, 0.f, 0.f)), 
      Vertex(glm::vec3(1.f, 1.f, -1.f), glm::vec3(1.f, 0.8f, 0.f)), // top-right corner
      Vertex(glm::vec3(1.f, 1.f, 1.f), glm::vec3(1.f, 0.8f, 0.f)), // top-left corner
      Vertex(glm::vec3(1.f, -1.f, 1.f), glm::vec3(0.f, 0.f, 0.f)),
      //left
      Vertex(glm::vec3(-1.f, -1.f, 1.f), glm::vec3(0.f, 0.f, 0.f)), // right-below corner
      Vertex(glm::vec3(-1.f, 1.f, 1.f), glm::vec3(1.f, 0.8f, 0.f)), // top-right corner
      Vertex(glm::vec3(-1.f, 1.f, -1.f), glm::vec3(1.f, 0.8f, 0.f)), // top-left corner
      Vertex(glm::vec3(-1.f, -1.f, -1.f), glm::vec3(0.f, 0.f, 0.f)),
      //back
      Vertex(glm::vec3(1.f, -1.f, -1.f), glm::vec3(0.f, 0.f, 0.f)), 
      Vertex(glm::vec3(1.f, 1.f, -1.f), glm::vec3(1.f, 0.8f, 0.f)), // top-left corner
      Vertex(glm::vec3(-1.f, 1.f, -1.f), glm::vec3(1.f, 0.8f, 0.f)), // top-right corner
      Vertex(glm::vec3(-1.f, -1.f, -1.f), glm::vec3(0.f, 0.f, 0.f))
   };

   std::vector<uint16_t> topIndexes{ 0, 1, 2, 3, 4, 5, 6, 7 };
   std::vector<uint16_t> sideIndexes{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15 };

   std::shared_ptr<Buffer> topBuffer = std::make_shared<Buffer>(topVertices, topIndexes);
   std::shared_ptr<Buffer> sideBuffer = std::make_shared<Buffer>(sideVertices, sideIndexes);

   mesh->AddBuffer(topBuffer);
   mesh->AddBuffer(sideBuffer);

   models.reserve(1);
   for (int i = 0; i < 1; ++i)
   {
      models.push_back(std::make_shared<Model>(mesh));
   }

   models[0]->SetPosition(glm::vec3(0, 0, 0));

   for (auto& iterator : models)
   {
      iterator->SetRotation(glm::vec3(0, 1.f, 0));
      iterator->SetScale(glm::vec3(1.f, 1.f, 1.f));

      World::GetWorld()->AddEntity(iterator);
   }

   camera->SetPosition(glm::vec3(3.f, 4.f, 7.f));
   camera->SetProjection(glm::perspective(45.f, 1.3f, 0.2f, 80.f));
   camera->SetViewport(glm::ivec4(0, 0, 0, 0));
   camera->SetClearColor(glm::vec3(0, 0, 0));

   World::GetWorld()->AddEntity(camera);

   // main loop
   double lastTime = glfwGetTime();

   while (!glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE))
   {
      // get delta time
      auto deltaTime = static_cast<float>(glfwGetTime() - lastTime);
      lastTime = glfwGetTime();

      // get window size
      int screenWidth, screenHeight;
      glfwGetWindowSize(win, &screenWidth, &screenHeight);

      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      World::GetWorld()->Update(deltaTime);
      World::GetWorld()->Draw();

      // refresh screen
      glfwSwapBuffers(win);
      glfwPollEvents();
   }

   // shutdown
   glfwTerminate();
}