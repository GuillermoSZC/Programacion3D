#pragma once
#include "Shader.h"
// @SINGLETON

class State 
{
public:


public:
   std::shared_ptr<Shader> defaultShader;
   glm::mat4 projectionMatrix;
   glm::mat4 viewMatrix;
   glm::mat4 modelMatrix;

protected:


private:
   State() = default;

public:
   static State* GetState();

protected:


private:


};

