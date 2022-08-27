#pragma once
#include "Texture.h"

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


public:
   const std::shared_ptr<Shader>& GetShader() const;
   std::shared_ptr<Shader>& GetShader();
   const std::shared_ptr<Texture>& GetTexture() const;
   std::shared_ptr<Texture>& GetTexture();

   void SetShader(const std::shared_ptr<Shader>& _shader);
   void SetTexture(const std::shared_ptr<Texture>& _texture);

   void Prepare();

protected:


private:


};