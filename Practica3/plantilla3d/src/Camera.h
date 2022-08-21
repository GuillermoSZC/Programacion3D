#pragma once
#include "Entity.h"
#include "../lib/glm/gtc/matrix_transform.hpp"


class Camera : public Entity
{
public:
   Camera() = default;
   Camera(float _width, float _height);
   ~Camera() = default;

public:


protected:


private:
   float width, height;

   glm::mat4 projection;
   glm::ivec4 viewport;
   glm::vec3 color;

public:
   const glm::mat4& GetProjection() const;
   const glm::ivec4& GetViewport() const;
   const glm::vec3& GetClearColor() const;

   void SetProjection(const glm::mat4& _projection);
   void SetViewport(const glm::ivec4& _viewport);
   void SetClearColor(const glm::vec3& _color);

   void Prepare();

protected:


private:


};

