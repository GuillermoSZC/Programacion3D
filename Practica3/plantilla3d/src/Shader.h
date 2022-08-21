#pragma once
#include "../glew/GL/glew.h"
#include <string>
#include "Vertex.h"
#include <iostream>

class Shader
{
public:
    Shader() = default;
    Shader(const std::string& _vertex, const std::string& _fragment);
    ~Shader() = default;

public:

protected:

private:
    uint32_t shaderId;
    const char* error;
    
    int location;
    int colorLoc;
    int textureLoc;

    glm::mat4 matrix;

public:
    void SetInt(int _loc, int _val) const;
    void SetFloat(int _loc, float _val) const;
    void SetVec3(int _loc, const glm::vec3& _vec) const;
    void SetVec4(int _loc, const glm::vec4& _vec) const;
    void SetMatrix(int _loc, const glm::mat4& _matrix) const;

    uint32_t GetId() const;
    const char* GetError();
    void Use() const;
    void SetupAttribs() const;
    int GetLocation(const char* _name) const;

    std::string ReadString(const std::string& _fileName);

protected:

private:

};

