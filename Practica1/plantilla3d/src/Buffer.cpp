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

void Buffer::Draw(const Shader& _shader, const glm::mat4& V, const glm::mat4& P) const
{
// ************************** MVP matrix calculation *********************************
    int locationAux;
    glm::mat4 M = glm::mat4(1.f);

    M = glm::translate(M, position);
    M = glm::rotate(M, speedRotation, glm::vec3(0.f, 1.f, 0.f));
    M = glm::scale(M, glm::vec3(1.f, 1.f, 1.f));

    glm::mat4 MVP = P * V * M;

    locationAux = _shader.GetLocation("mvp");
    _shader.SetMatrix(locationAux, MVP);

    glBindBuffer(GL_ARRAY_BUFFER, idArray[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, idArray[1]);
    _shader.SetupAttribs();
    glDrawElements(GL_TRIANGLES, indexes.size(), GL_UNSIGNED_SHORT, nullptr);
}

void Buffer::Update(float _deltaTime)
{
    speedRotation += _deltaTime;
}
