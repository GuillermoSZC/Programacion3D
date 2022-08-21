#include "Mesh.h"

Mesh::~Mesh()
{
   buffer.clear();
}

void Mesh::AddBuffer(const std::shared_ptr<Buffer>& _buffer, const std::shared_ptr<Shader>& _shader)
{
   _buffer->SetShader(_shader);
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

void Mesh::Draw()
{
   for (auto& it : buffer)
   {
      it->Draw();
   }
}
