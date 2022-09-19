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
      shader = State::GetState()->defaultShader;
      return shader;
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

glm::vec4 Material::GetColor()
{
   return color;
}

uint8_t Material::GetShininess()
{
   return shininess;
}

void Material::SetShader(const std::shared_ptr<Shader>& _shader)
{
   shader = _shader;
}

void Material::SetTexture(const std::shared_ptr<Texture>& _texture)
{
   texture = _texture;
}

void Material::SetColor(glm::vec4 _color)
{
   color = _color;
}

void Material::SetShininess(uint8_t _shininess)
{
   shininess = _shininess;
}

void Material::Prepare()
{
   std::shared_ptr<Shader> auxShader = GetShader();
   auxShader->Use();

   if (texture)
   {
      texture->Bind();
   }
   
   auxShader->SetMatrix(auxShader->GetLocation("mvp"), State::GetState()->projectionMatrix * State::GetState()->viewMatrix * State::GetState()->modelMatrix);

   auxShader->SetInt(auxShader->GetLocation("texSampler"), 0);

   glm::mat4 mv = State::GetState()->viewMatrix * State::GetState()->modelMatrix;
   auxShader->SetMatrix(auxShader->GetLocation("mv"), mv);

   glm::mat4 normalMatrix = glm::inverse(mv);
   normalMatrix = glm::transpose(normalMatrix);
   auxShader->SetMatrix(auxShader->GetLocation("nmatrix"), normalMatrix);

   auxShader->SetInt(auxShader->GetLocation("numLights"), State::GetState()->lights.size());

   int i = 0;
   for (auto& iterator : State::GetState()->lights)
   {
      iterator->Prepare(i, auxShader);
      i++;
   }

   auxShader->SetInt(auxShader->GetLocation("_numLights"), State::GetState()->lights.size());

   auxShader->SetVec3(auxShader->GetLocation("_globalAmbient"), State::GetState()->ambient);

   auxShader->SetVec4(auxShader->GetLocation("mat.ambient"), glm::vec4(color));
   auxShader->SetVec4(auxShader->GetLocation("mat.diffuse"), glm::vec4(color));
   auxShader->SetVec3(auxShader->GetLocation("mat.specular"), glm::vec3(color));
   auxShader->SetFloat(auxShader->GetLocation("mat.shininess"), shininess);
}
