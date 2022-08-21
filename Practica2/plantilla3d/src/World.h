#pragma once
#include "Entity.h"
#include "Camera.h"
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

public:   
   static World* GetWorld();

   void AddEntity(const std::shared_ptr<Entity>& _entity);
   void RemoveEntity(const std::shared_ptr<Entity>& _entity);
   std::shared_ptr<Entity>& GetEntity(size_t _index);
   size_t GetNumEntities() const;

   void Update(float _deltaTime);
   void Draw();

protected:


private:


};

