#include "Vertex.h"

Vertex::Vertex(glm::vec3 _position, glm::vec3 _color, glm::vec2 _texture, glm::vec3 _normal)
{
    vertexPosition = _position;
    vertexColor = _color;
    texture = _texture;
    normal = _normal;
}