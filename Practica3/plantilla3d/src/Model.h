#pragma once
#include "Entity.h"
#include "Mesh.h"
#include "../lib/glm/gtc/matrix_transform.hpp"

class Model : public Entity
{
public:
  Model(const std::shared_ptr<Mesh>& _mesh);
  ~Model() = default;

public:
   

protected:


private:
   float rotation;
   std::shared_ptr<Mesh> mesh;

public:
  virtual void Draw() override;
  virtual void Update(float _deltaTime) override;


protected:


private:


};

