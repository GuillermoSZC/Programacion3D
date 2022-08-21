#include "Buffer.h"
#include "Shader.h"
#include "../lib/glm/gtc/matrix_transform.hpp"

Buffer::Buffer(std::vector<Vertex>& _vertex, std::vector<uint16_t>& _indexes)
{
   vertex = _vertex;
   indexes = _indexes;

   glGenBuffers(2, idArray.data());

   glBindBuffer(GL_ARRAY_BUFFER, idArray[0]);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idArray[1]);

   glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * vertex.size(), vertex.data(), GL_STATIC_DRAW);
   glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint16_t) * indexes.size(), indexes.data(), GL_STATIC_DRAW);
}

Buffer::~Buffer()
{
   idArray.empty();
}

void Buffer::SetShader(std::shared_ptr<Shader> _shader)
{
   shader = _shader;
}

std::shared_ptr<Shader> Buffer::GetShader()
{
   return shader;
}

void Buffer::Draw() const
{
   // ************************** MVP matrix calculation *********************************
   int locationAux;
   glm::mat4 MVP = State::GetState()->projectionMatrix * State::GetState()->viewMatrix * State::GetState()->modelMatrix;

   locationAux = shader->GetLocation("mvp");
   shader->SetMatrix(locationAux, MVP);

   glBindBuffer(GL_ARRAY_BUFFER, idArray[0]);
   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idArray[1]);
   shader->SetupAttribs();
   glDrawElements(GL_QUADS, indexes.size(), GL_UNSIGNED_SHORT, nullptr);
}