#include "InputManager.h"

InputManager* InputManager::GetState()
{
   static auto inputManager = new InputManager();

   return inputManager;
}

void InputManager::UpdateCameraPosition(GLFWwindow*& _window, std::shared_ptr<Camera>& _camera, float _deltaTime)
{
   float speed = 10.f * _deltaTime;

   if (glfwGetKey(_window, GLFW_KEY_W))
   {
      _camera->SetPosition(glm::vec3(_camera->GetPosition() + speed * _camera->updateFront));
   }
   if (glfwGetKey(_window, GLFW_KEY_A))
   {
      _camera->SetPosition(glm::vec3(_camera->GetPosition() - glm::normalize(
         glm::cross(_camera->updateFront, _camera->updateUp)) * speed));
   }

   if (glfwGetKey(_window, GLFW_KEY_S))
   {
      _camera->SetPosition(glm::vec3(_camera->GetPosition() - speed * _camera->updateFront));
   }

   if (glfwGetKey(_window, GLFW_KEY_D))
   {
      _camera->SetPosition(glm::vec3(_camera->GetPosition() + glm::normalize(
         glm::cross(_camera->updateFront, _camera->updateUp)) * speed));
   }

   if (glfwGetKey(_window, GLFW_KEY_Q))
   {
      _camera->SetPosition(glm::vec3(_camera->GetPosition() + speed * _camera->updateUp));
   }

   if (glfwGetKey(_window, GLFW_KEY_E))
   {
      _camera->SetPosition(glm::vec3(_camera->GetPosition() - speed * _camera->updateUp));
   }
}
