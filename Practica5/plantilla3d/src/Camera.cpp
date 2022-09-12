#include "Camera.h"

Camera::Camera(float _width, float _height) :
   width(_width),
   height(_height)
{

}

const glm::mat4& Camera::GetProjection() const
{
   return projection;
}

const glm::ivec4& Camera::GetViewport() const
{
   return viewport;
}

const glm::vec3& Camera::GetClearColor() const
{
   return color;
}

void Camera::SetProjection(const glm::mat4& _projection)
{
   projection = _projection;
}

void Camera::SetViewport(const glm::ivec4& _viewport)
{
   viewport = _viewport;
}

void Camera::SetClearColor(const glm::vec3& _color)
{
   color = _color;
}

void Camera::Prepare()
{
   State::GetState()->projectionMatrix = projection;
   State::GetState()->viewMatrix = glm::lookAt(GetPosition(), GetPosition() + updateFront, updateUp);

   glViewport(viewport.x, viewport.y, width, height);
   glScissor(viewport.x, viewport.y, width, height);

   glClearColor(color.x, color.y, color.z, 1.f);
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
