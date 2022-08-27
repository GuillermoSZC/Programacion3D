#include "Material.h"
#include "State.h"
#include "Shader.h"



Material::Material(const std::shared_ptr<Texture>& _texture, const std::shared_ptr<Shader>& _shader)
{
   if (_texture)
   {
      texture = _texture;
   }

   if (_shader)
   {
      shader = _shader;
   }
   else
   {
      shader = State::GetState()->defaultShader;
   }
}

const std::shared_ptr<Shader>& Material::GetShader() const
{
   if (!shader)
   {
      return State::GetState()->defaultShader;
   }

   return shader;
}

std::shared_ptr<Shader>& Material::GetShader()
{
   if (!shader)
   {
      return State::GetState()->defaultShader;
   }

   return shader;
}

const std::shared_ptr<Texture>& Material::GetTexture() const
{
   return texture;
}

std::shared_ptr<Texture>& Material::GetTexture()
{
   return texture;
}

void Material::SetShader(const std::shared_ptr<Shader>& _shader)
{
   shader = _shader;
}

void Material::SetTexture(const std::shared_ptr<Texture>& _texture)
{
   texture = _texture;
}

void Material::Prepare()
{
   shader->Use();

   if (texture)
   {
      texture->Bind();
   }

   shader->SetInt(shader->GetLocation("texSampler"), 0);
}
