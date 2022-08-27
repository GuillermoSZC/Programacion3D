#include "Vertex.h"

Vertex::Vertex(glm::vec3 _position, glm::vec3 _color, glm::ivec2 _texture)
{
    vertexPosition = _position;
    vertexColor = _color;
    texture = _texture;
}