#pragma once

#define STB_IMAGE_IMPLEMENTATION

#include <memory>
#include "glm.hpp"


class Texture
{
public:
   Texture() = default;
   ~Texture() = default;

public:


protected:


private:
   int width, height;
   uint32_t texID;

public:
   static std::shared_ptr<Texture> Load(const char* _fileName);

   uint32_t GetID() const;
   const glm::ivec2& GetSize() const;
   void Bind() const;

protected:


private:


};