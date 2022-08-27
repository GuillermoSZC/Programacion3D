#include "Mesh.h"
#include "Material.h"

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

void Mesh::Draw()
{
   for (auto& it : buffer)
   {
      it->GetMaterial().Prepare();
      it->Draw();
   }
}
