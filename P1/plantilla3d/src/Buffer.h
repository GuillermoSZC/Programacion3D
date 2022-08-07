#pragma once

#include "Vertex.h"
#include <array>
#include <vector>

class Shader;
class Buffer
{
public:
    Buffer() = default;
    Buffer(std::vector<Vertex>& _vertex, std::vector<uint16_t>& _indexes);
    ~Buffer();

public:    
    glm::vec3 position;
    float speedRotation;

protected:

private:
    std::vector<Vertex> vertex;
    std::vector<uint16_t> indexes;
    std::array<uint32_t, 2> idArray;

public:
    void Draw(const Shader& _shader, const glm::mat4& V, const glm::mat4& P) const;
    void Update(float _deltaTime);

protected:

private:

};

