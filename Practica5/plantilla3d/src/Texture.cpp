#include "Texture.h"
#include "../lib/stb_image.h"
#include "../lib/glew/GL/glew.h"

std::shared_ptr<Texture> Texture::Load(const char* _fileName)
{
   std::shared_ptr<Texture> auxTex = std::make_shared<Texture>();
   stbi_set_flip_vertically_on_load(true);
   unsigned char* buffer = stbi_load(_fileName, &auxTex->width, &auxTex->height, nullptr, 4);

   if (buffer)
   {
      glGenTextures(1, &auxTex->texID);

      glBindTexture(GL_TEXTURE_2D, auxTex->texID);

      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

      glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, auxTex->width, auxTex->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, buffer);

      glGenerateMipmap(GL_TEXTURE_2D);

      stbi_image_free(buffer);
   }
   else
   {
      auxTex.reset();
      auxTex = nullptr;
   }

   return auxTex;
}

uint32_t Texture::GetID() const
{
   return texID;
}

const glm::ivec2& Texture::GetSize() const
{
   return glm::ivec2(width, height);
}

void Texture::Bind() const
{
   if (texID)
   {
      glBindTexture(GL_TEXTURE_2D, texID);
   }
}

