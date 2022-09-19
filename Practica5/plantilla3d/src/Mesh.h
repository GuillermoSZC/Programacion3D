#pragma once
#include "Buffer.h"
#include "Shader.h"

class Material;

class Mesh
{
public:
   Mesh() = default;
   ~Mesh();

public:


protected:


private:
   std::vector<std::shared_ptr<Buffer>> buffer;
   std::vector<Material*> materials;

public:
   void Draw();
   void AddBuffer(const std::shared_ptr<Buffer>& _buffer, Material* _material);
   size_t GetNumBuffers() const;
   size_t GetNumMaterials() const;

   const std::shared_ptr<Buffer>& GetBuffer(size_t _index) const;
   std::shared_ptr<Buffer>& GetBuffer(size_t _index);
   const Material* GetMaterial(size_t _index) const;
   Material* GetMaterial(size_t _index);
   static std::shared_ptr<Mesh> Load(const char* _fileName, const std::shared_ptr<Shader>& _shader = nullptr);

protected:


private:


};

