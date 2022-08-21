#pragma once

#include "Vertex.h"
#include "State.h"
#include <array>
#include <vector>
#include <memory>

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
   std::shared_ptr<Shader> shader;

public:
   void SetShader(std::shared_ptr<Shader> _shader);
   std::shared_ptr<Shader> GetShader();

   void Draw() const;

protected:

private:

};

