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
#include "InputManager.h"
#include "Light.h"

#include "../lib/glm/gtc/matrix_transform.hpp"

#define SCREEN_WIDTH 1024
#define SCREEN_HEIGHT 768
#define PI 3.14159265359

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
   
   const float fixed = 1.f / 60.f;
   float angle = 0.f;

   std::shared_ptr<Camera> camera = std::make_shared<Camera>(SCREEN_WIDTH, SCREEN_HEIGHT);
   camera->SetPosition(glm::vec3(8.f, 5.f, 40.f));
   camera->SetRotation(glm::vec3(-20.f * PI / 180.f, 0.f, 0.f));
   camera->SetProjection(glm::perspective(45.f, 1.3f, 0.2f, 80.f));
   camera->SetViewport(glm::ivec4(0.f, 0.f, 0.f, 0.f));
   camera->SetClearColor(glm::vec3(0.f, 0.f, 0.f));

   World::GetWorld()->AddEntity(camera);


   std::vector<std::shared_ptr<Model>> models;
   std::shared_ptr<Mesh> boxStackSM = std::make_shared<Mesh>()->Load("data/box_stack.obj", State::GetState()->defaultShader);
   std::shared_ptr<Mesh> cowboySM = std::make_shared<Mesh>()->Load("data/gunslinger.obj", State::GetState()->defaultShader);
   std::shared_ptr<Light> directionalLight(new Light());
   std::shared_ptr<Light> pointLight(new Light());

   directionalLight->SetColor(glm::vec3(1.f, 1.f, 1.f));
   directionalLight->SetType(LightTypes::DirectionalLight);
   directionalLight->SetPosition(glm::vec3(1.f, 1.f, 1.f));
   directionalLight->SetLinearAttenuation(1.f);
   World::GetWorld()->AddEntity(directionalLight);

   pointLight->SetColor(glm::vec3(1.f, 0.f, 0.f));
   pointLight->SetType(LightTypes::PointLight);
   pointLight->SetPosition(glm::vec3(30.f, 9.f, 2.f));
   pointLight->SetLinearAttenuation(0.2f);
   World::GetWorld()->AddEntity(pointLight);

   World::GetWorld()->SetAmbient(glm::vec3(0.2f, 0.2f, 0.2f));
   
   models.push_back(std::make_shared<Model>(boxStackSM));
   models.push_back(std::make_shared<Model>(cowboySM));
   
   models[0]->SetPosition(glm::vec3(-7.f, 0.f, 2.f));
   models[1]->SetPosition(glm::vec3(7.f, 0.f, 2.f));
   models[0]->SetScale(glm::vec3(1.f, 1.f, 1.f));
   models[1]->SetScale(glm::vec3(1.f, 1.f, 1.f));

   for (auto& iterator : models)
   {
      iterator->SetRotation(glm::vec3(0.f, 1.f, 0.f));
      World::GetWorld()->AddEntity(iterator);
   }



   // main loop
   double lastTime = glfwGetTime();
   double deltaTime = 0.0;

   while (!glfwWindowShouldClose(win) && !glfwGetKey(win, GLFW_KEY_ESCAPE))
   {
      // get delta time
      deltaTime += glfwGetTime() - lastTime;
      lastTime = glfwGetTime();

      // get window size
      int screenWidth, screenHeight;
      glfwGetWindowSize(win, &screenWidth, &screenHeight);

      while (deltaTime >= fixed)
      {
         deltaTime -= fixed;

         glm::vec3 currentPosition = pointLight->GetPosition();

         currentPosition.x = 7 + (30 * cos((angle * PI) / 180.f));
         currentPosition.z = 2 + (30 * sin((angle * PI) / 180.f));

         pointLight->SetPosition(currentPosition);
         models[0]->SetPosition(currentPosition);

         angle += 50 * fixed;

         if (angle > 360.f)
         {
            angle -= 360.f;
         }

         World::GetWorld()->Update(fixed);
      }
      
      World::GetWorld()->Draw();
      
      // MOVE WITH W-A-S-D AND E-Q
      InputManager::UpdateCameraPosition(win, camera, deltaTime);

      // refresh screen
      glfwSwapBuffers(win);
      glfwPollEvents();
   }

   // shutdown
   glfwTerminate();
}