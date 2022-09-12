#pragma once
#include "Texture.h"
#include "Light.h"

class Shader;

class Material
{
public:
   Material(const std::shared_ptr<Texture>& _texture = nullptr, const std::shared_ptr<Shader>& _shader = nullptr);
   ~Material() = default;

public:
   

protected:


private:
   std::shared_ptr<Shader> shader;
   std::shared_ptr<Texture> texture;
   glm::vec4 color;
   uint8_t shininess;

public:
   const std::shared_ptr<Shader>& GetShader() const;
   std::shared_ptr<Shader>& GetShader();
   const std::shared_ptr<Texture>& GetTexture() const;
   std::shared_ptr<Texture>& GetTexture();
   glm::vec4 GetColor();
   uint8_t GetShininess();


   void SetShader(const std::shared_ptr<Shader>& _shader);
   void SetTexture(const std::shared_ptr<Texture>& _texture);
   void SetColor(glm::vec4 _color);
   void SetShininess(uint8_t _shininess);

   void Prepare();

protected:


private:


};