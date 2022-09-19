#pragma once

#include "Vertex.h"
#include "State.h"
#include <array>
#include <vector>
#include <memory>
#include "Material.h"

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
   Material material;

public:
   void SetShader(std::shared_ptr<Shader> _shader);
   void SetMaterial(const Material& _material);

   std::shared_ptr<Shader> GetShader();
   Material& GetMaterial();

   void Draw(const std::shared_ptr<Shader>& _shader) const;

protected:

private:

};

