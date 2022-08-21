#pragma once
#include "../lib/glm/glm.hpp"

class Vertex
{
public:
    Vertex() = default;
    Vertex(glm::vec3 _position, glm::vec3 _color, glm::ivec2 _texture);
    ~Vertex() = default;

public:
    glm::vec3 vertexPosition;
    glm::vec3 vertexColor;
    glm::ivec2 texture;

protected:

private:


public:

protected:

private:


};

