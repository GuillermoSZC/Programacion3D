#include "Light.h"

Light::Light() : 
   lightMode(LightTypes::DirectionalLight), color(0.f, 0.f, 0.f, 0.f), linearAttenuation(0.f)
{

}

#pragma region GETTERS_AND_SETTERS
LightTypes Light::GetType()
{
   return lightMode;
}

float Light::GetLinearAttenuation() const
{
   return linearAttenuation;
}

const glm::vec3& Light::GetColor() const
{
   return color;
}

void Light::SetType(LightTypes _type)
{
   lightMode = _type;
   color.w = int(_type);
}

void Light::SetColor(const glm::vec3 _color)
{
   color = glm::vec4(_color.x, _color.y, _color.z, 0.f);
}

void Light::SetLinearAttenuation(float _attenuation)
{
   linearAttenuation = _attenuation;
}
#pragma endregion

void Light::Prepare(int _index, std::shared_ptr<Shader> _shader) const
{
   std::string light = "lights[";
   std::string ambient = "].ambient";
   std::string diffuse  = "].diffuse";
   std::string specular = "].specular";
   std::string position = "].position";
   std::string boolPointLight = "].boolPointLight";
   std::string attenuation = "].linarAttenuation";
   std::string index = std::to_string(_index);

   int ambientLocation = _shader->GetLocation((light + index + ambient).c_str());
   _shader->SetVec4(ambientLocation, color);
   
   int diffuseLocation = _shader->GetLocation((light + index + diffuse).c_str());
   _shader->SetVec4(diffuseLocation, color);

   int specularLocation = _shader->GetLocation((light + index + specular).c_str());
   _shader->SetVec4(specularLocation, color);

   int positionLocation = _shader->GetLocation((light + index + position).c_str());
   _shader->SetVec3(positionLocation, vPosition);

   int auxType;
   if (lightMode == LightTypes::PointLight)
   {
      auxType = 1;
   }
   else
   {
      auxType = 0;
   }

   int boolPointLightLocation = _shader->GetLocation((light + index + boolPointLight).c_str());
   _shader->SetFloat(boolPointLightLocation, auxType);

   int attenuationLocation = _shader->GetLocation((light + index + attenuation).c_str());
   _shader->SetFloat(attenuationLocation, linearAttenuation);
}
