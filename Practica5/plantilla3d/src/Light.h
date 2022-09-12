#pragma once

#include "Entity.h"
#include <glm.hpp>

class Shader;

enum class LightTypes
{
   DirectionalLight = 0,
   PointLight = 1
};

class Light : public Entity
{
public:
   Light();
   ~Light() = default;

public:

protected:

private:
   LightTypes lightMode;
   glm::vec4 color;
   float linearAttenuation;

public:
   LightTypes GetType();
   float GetLinearAttenuation() const;
   const glm::vec3& GetColor() const;

   void SetType(LightTypes _type);
   void SetColor(const glm::vec3 _color);
   void SetLinearAttenuation(float _attenuation);

   void Prepare(int _index, std::shared_ptr<Shader> _shader) const;

protected:

private:

};
