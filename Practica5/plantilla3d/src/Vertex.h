#pragma once
#include "glm.hpp"

class Vertex
{
public:
   Vertex(glm::vec3 _pos, glm::vec3 _color, glm::vec2 _textureCoord, glm::vec3 _normal = glm::vec3(0.f, 0.f, 0.f));

public:
   glm::vec3 vertexPosition;
   glm::vec3 vertexColor;
   glm::vec2 texture;
   glm::vec3 normal;

protected:

private:

public:

protected:

private:

};
