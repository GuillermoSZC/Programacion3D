#pragma once
#include "Buffer.h"
#include "Shader.h"

class Mesh
{
public:
   Mesh() = default;
   ~Mesh();

public:


protected:


private:
   std::vector<std::shared_ptr<Buffer>> buffer;

public:
   void Draw();
   void AddBuffer(const std::shared_ptr<Buffer>& _buffer,
      const std::shared_ptr<Shader>& _shader = State::GetState()->defaultShader);
   size_t GetNumBuffers() const;

   const std::shared_ptr<Buffer>& GetBuffer(size_t _index) const;
   std::shared_ptr<Buffer>& GetBuffer(size_t _index);

protected:


private:


};

