#pragma once

#include "Shader.h"
#include <memory>
#include <vector>
#include <list>

class Light;

class State
{
public:

public:
   std::shared_ptr<Shader> defaultShader;
   glm::mat4 projectionMatrix;
   glm::mat4 viewMatrix;
   glm::mat4 modelMatrix;
   std::list<std::shared_ptr<Light>> lights;
   glm::vec3 ambient;

protected:

private:
   State() = default;

public:
   static State* GetState();

protected:


private:


};

