#pragma once
#include "../lib/glm/glm.hpp"
#include <iostream>
#include "State.h"

class Entity
{
public:
   Entity();
   virtual ~Entity() = default;

public:


protected:


private:
   glm::vec3 vPosition;
   glm::vec3 vRotation;
   glm::vec3 vScale;

public:
   const glm::vec3& GetPosition() const;
   const glm::vec3& GetRotation() const;
   const glm::vec3& GetScale() const;

   void  SetPosition(const glm::vec3& _position);
   const void SetRotation(const glm::vec3& _rotation);
   void SetScale(const glm::vec3& _scale);

   void Move(const glm::vec3& _vec);
   virtual void Update(float _deltaTime);
   virtual void Draw();

protected:


private:


};