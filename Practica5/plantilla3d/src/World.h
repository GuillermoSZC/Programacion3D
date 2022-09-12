#pragma once
#include "Entity.h"
#include "Camera.h"
#include "Light.h"
#include "State.h"
#include <list>
// @SINGLETON

class World 
{
public:
   
public:


protected:


private:
   World() = default;

   std::list<std::shared_ptr<Entity>> entities;
   std::list<std::shared_ptr<Camera>> cameras;
   std::list<std::shared_ptr<Light>> lights;
   glm::vec3 ambient;

public:   
   static World* GetWorld();

   void AddEntity(const std::shared_ptr<Entity>& _entity);
   void RemoveEntity(const std::shared_ptr<Entity>& _entity);
   std::shared_ptr<Entity>& GetEntity(size_t _index);
   size_t GetNumEntities() const;
   glm::vec3 GetAmbient();
   void SetAmbient(glm::vec3 _ambient);

   void Update(float _deltaTime);
   void Draw();

protected:


private:


};

