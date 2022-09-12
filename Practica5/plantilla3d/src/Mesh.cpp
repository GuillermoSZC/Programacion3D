#define TINYOBJLOADER_IMPLEMENTATION

#include "Mesh.h"
#include "Material.h"
#include "../lib/tinyobjloader-master/tiny_obj_loader.h"

Mesh::~Mesh()
{
   buffer.clear();
}

void Mesh::AddBuffer(const std::shared_ptr<Buffer>& _buffer, const Material& _material)
{
   _buffer->SetMaterial(_material);
   buffer.push_back(_buffer);
}

size_t Mesh::GetNumBuffers() const
{
   return buffer.size();
}

const std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t _index) const
{
   return buffer[_index];
}

std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t _index)
{
   return buffer[_index];
}

const Material& Mesh::GetMaterial(size_t _index) const
{
   return buffer[_index]->GetMaterial();
}

Material& Mesh::GetMaterial(size_t _index)
{
   return buffer[_index]->GetMaterial();
}

std::shared_ptr<Mesh> Mesh::Load(const char* _fileName, const std::shared_ptr<Shader>& _shader)
{
   std::shared_ptr<Mesh> auxMesh = std::make_shared<Mesh>();
   std::shared_ptr<Buffer> buffer;
   tinyobj::attrib_t attrib;
   std::vector<tinyobj::shape_t> shapesVec;
   std::vector<tinyobj::material_t> materialsVec;
   std::string warn, err, route;
   std::vector<Vertex> vertex;
   std::vector<uint16_t> indexes;
   std::shared_ptr<Texture> tex;
   Material mat;

   if (!tinyobj::LoadObj(&attrib, &shapesVec, &materialsVec, &warn, &err, _fileName, "data"))
   {
      throw std::runtime_error(warn + err);
   }

   for (int i = 0; i < shapesVec.size(); ++i)
   {
      vertex.clear();

      for (const auto& index : shapesVec[i].mesh.indices)
      {
         auto vertexAux = new Vertex(
            glm::vec3(
               attrib.vertices[3 * index.vertex_index + 0],
               attrib.vertices[3 * index.vertex_index + 1],
               attrib.vertices[3 * index.vertex_index + 2]),
            glm::vec3(1.f, 1.f, 1.f),
            glm::vec2(
               attrib.texcoords[2 * index.texcoord_index + 0],
               1.f - attrib.texcoords[2 * index.texcoord_index + 1]));

         vertex.push_back(*vertexAux);
         indexes.push_back(indexes.size());
      }

      route = "data/";
      route += materialsVec[i].ambient_texname;

      tex = std::make_shared<Texture>()->Load(route.c_str());
      mat = Material(tex, State::GetState()->defaultShader);
      buffer = std::make_shared<Buffer>(vertex, indexes);
      auxMesh->AddBuffer(buffer, mat);
   }

   return auxMesh;
}

void Mesh::Draw()
{
   for (auto& it : buffer)
   {
      it->GetMaterial().Prepare();
      it->Draw();
   }
}
