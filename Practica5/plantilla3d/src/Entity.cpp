#include "Entity.h"

Entity::Entity()
{
   vPosition = glm::vec3(0.f, 0.f, 0.f);
   vRotation = glm::vec3(0.f, 0.f, 0.f);
   vScale    = glm::vec3(0.f, 0.f, 0.f);
}

const glm::vec3& Entity::GetPosition() const
{
   return vPosition;
}

const glm::vec3& Entity::GetRotation() const
{
   return vRotation;
}

const glm::vec3& Entity::GetScale() const
{
   return vScale;
}

void Entity::SetPosition(const glm::vec3& _position)
{
   vPosition = _position;
}

const void Entity::SetRotation(const glm::vec3& _rotation)
{
   vRotation = _rotation;
}

void Entity::SetScale(const glm::vec3& _scale)
{
   vScale = _scale;
}

void Entity::Move(const glm::vec3& _vec)
{
   vPosition += _vec;
}

void Entity::Update(float _deltaTime)
{

}

void Entity::Draw()
{

}
