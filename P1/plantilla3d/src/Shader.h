#pragma once
#include "../glew/GL/glew.h"
#include <string>
#include "Vertex.h"


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

    glm::mat4 matrix;

public:
    void SetInt(int _loc, int _val);
    void SetFloat(int _loc, float _val);
    void SetVec3(int _loc, const glm::vec3& _vec);
    void SetVec4(int _loc, const glm::vec4& _vec);
    void SetMatrix(int _loc, const glm::mat4& _matrix) const;

    uint32_t GetId() const;
    const char* GetError() const;
    void Use() const;
    void SetupAttribs() const;
    int GetLocation(const char* _name) const;

    std::string ReadString(const std::string& _fileName);

protected:

private:

};

