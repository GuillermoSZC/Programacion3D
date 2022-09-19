#define TINYOBJLOADER_IMPLEMENTATION

#include "Mesh.h"
#include "Material.h"
#include "../lib/tinyobjloader-master/tiny_obj_loader.h"

Mesh::~Mesh()
{
   buffer.clear();
}

void Mesh::AddBuffer(const std::shared_ptr<Buffer>& _buffer, Material* _material)
{
   buffer.push_back(_buffer);
   materials.push_back(_material);
}

size_t Mesh::GetNumBuffers() const
{
   return buffer.size();
}

size_t Mesh::GetNumMaterials() const
{
   return materials.size();
}

const std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t _index) const
{
   return buffer[_index];
}

std::shared_ptr<Buffer>& Mesh::GetBuffer(size_t _index)
{
   return buffer[_index];
}

const Material* Mesh::GetMaterial(size_t _index) const
{
   if (_index < (materials.size() - 1))
   {
      return materials[_index];
   }

   return nullptr;
}

Material* Mesh::GetMaterial(size_t _index)
{
   if (_index < (materials.size() - 1))
   {
      return materials[_index];
   }

   return nullptr;
}

std::shared_ptr<Mesh> Mesh::Load(const char* _fileName, const std::shared_ptr<Shader>& _shader)
{
   std::shared_ptr<Mesh> auxMesh = std::make_shared<Mesh>();
   std::shared_ptr<Buffer> auxBuffer;
   tinyobj::attrib_t attrib;
   std::vector<tinyobj::shape_t> shapesVec;
   std::vector<tinyobj::material_t> materialsVec;
   std::string warn, err, route;
   std::vector<Vertex> vertex;
   std::vector<uint16_t> indexes;
   std::shared_ptr<Texture> tex;
   Material* mat;

   if (!tinyobj::LoadObj(&attrib, &shapesVec, &materialsVec, &warn, &err, _fileName, "data"))
   {
      throw std::runtime_error(warn + err);
   }

   for (int i = 0; i < shapesVec.size(); ++i)
   {
      vertex.clear();

      for (unsigned int y = 0; y < shapesVec[i].mesh.indices.size(); ++y)
      {

         auto vertexAux = new Vertex();
         vertexAux->vertexPosition.x = attrib.vertices[3 * shapesVec[i].mesh.indices[y].vertex_index + 0];
         vertexAux->vertexPosition.y = attrib.vertices[3 * shapesVec[i].mesh.indices[y].vertex_index + 1];
         vertexAux->vertexPosition.z = attrib.vertices[3 * shapesVec[i].mesh.indices[y].vertex_index + 2];
         vertexAux->vertexColor.r = 1;
         vertexAux->vertexColor.g = 1;
         vertexAux->vertexColor.b = 1;
         vertexAux->texture.x = attrib.texcoords[2 * shapesVec[i].mesh.indices[y].texcoord_index + 0];
         vertexAux->texture.y = attrib.texcoords[2 * shapesVec[i].mesh.indices[y].texcoord_index + 1];
         vertexAux->normal.x = attrib.normals[3 * shapesVec[i].mesh.indices[y].normal_index + 0];
         vertexAux->normal.y = attrib.normals[3 * shapesVec[i].mesh.indices[y].normal_index + 1];
         vertexAux->normal.z = attrib.normals[3 * shapesVec[i].mesh.indices[y].normal_index + 2];

         vertex.push_back(*vertexAux);
         indexes.push_back(y);
      }

      route = "data/";

      auxBuffer = std::make_shared<Buffer>(vertex, indexes);
      route = route.append(materialsVec[i].ambient_texname);
      mat = new Material(std::make_shared<Texture>()->Load(route.c_str()));

      mat->SetShininess(10);
      mat->SetColor(glm::vec4(materialsVec[i].ambient[0], materialsVec[i].ambient[1], materialsVec[i].ambient[2], 1));

      auxMesh->AddBuffer(auxBuffer, mat);
   }

   return auxMesh;
}

void Mesh::Draw()
{
   size_t bufferSize = buffer.size();

   for (size_t i = 0; i < bufferSize; ++i)
   {
      materials[i]->Prepare();
      buffer[i]->Draw(materials[i]->GetShader());
   }
}
