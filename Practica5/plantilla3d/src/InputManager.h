#include "Camera.h"
#include "../glfw/glfw3.h"

class InputManager
{
public:


public:


protected:


private:
   InputManager() = default;

public:
   static InputManager* GetState();

   static void UpdateCameraPosition(GLFWwindow*& _window, std::shared_ptr<Camera>& _camera, float _deltaTime);

protected:


private:


};