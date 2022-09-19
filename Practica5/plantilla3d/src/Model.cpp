#include "Model.h"

Model::Model(const std::shared_ptr<Mesh>& _mesh) :
   mesh(_mesh),
   rotation(0.f)
{

}

void Model::Draw()
{
   State::GetState()->modelMatrix = glm::mat4(1.0f);
   State::GetState()->modelMatrix = glm::translate(State::GetState()->modelMatrix, GetPosition());
   State::GetState()->modelMatrix = glm::rotate(State::GetState()->modelMatrix, rotation, GetRotation());
   State::GetState()->modelMatrix = glm::scale(State::GetState()->modelMatrix, GetScale());

   mesh->Draw();
}

void Model::Update(float _deltaTime)
{
   // rotation += _deltaTime;
}
