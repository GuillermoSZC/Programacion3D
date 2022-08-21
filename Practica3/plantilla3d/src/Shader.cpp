#include "Shader.h"
#include "gtc/type_ptr.hpp"
#include <sstream>
#include <fstream>


Shader::Shader(const std::string& _vertex, const std::string& _fragment)
{
   int vertexAux;

   std::string vertexString = ReadString(_vertex);
   const char* vertexShaderStr = vertexString.c_str();
   std::string fragmentString = ReadString(_fragment);
   const char* fragmentShaderStr = fragmentString.c_str();
   uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);
   uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

   glShaderSource(vertexShader, 1, &vertexShaderStr, nullptr);
   glCompileShader(vertexShader);
   glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &vertexAux);

   if (vertexAux == GL_FALSE)
   {
      char auxErr[1024];

      glGetShaderInfoLog(vertexShader, sizeof(auxErr), nullptr, auxErr);
      error = auxErr;
      glDeleteShader(vertexShader);

      return;
   }

   glShaderSource(fragmentShader, 1, &fragmentShaderStr, nullptr);
   glCompileShader(fragmentShader);
   glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &vertexAux);

   if (vertexAux == GL_FALSE)
   {
      char auxErr[1024];

      glGetShaderInfoLog(fragmentShader, sizeof(auxErr), nullptr, auxErr);
      error = auxErr;
      glDeleteShader(fragmentShader);

      return;
   }

   shaderId = glCreateProgram();

   glAttachShader(shaderId, vertexShader);
   glAttachShader(shaderId, fragmentShader);
   glLinkProgram(shaderId);
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   glGetProgramiv(shaderId, GL_LINK_STATUS, &vertexAux);

   if (vertexAux == GL_FALSE) {
      char errorLog[1024];

      glGetProgramInfoLog(shaderId, sizeof(errorLog), nullptr, errorLog);
      error = errorLog;
      glDeleteProgram(shaderId);
      shaderId = 0;

      return;
   }

   location = glGetAttribLocation(shaderId, "vpos");
   colorLoc = glGetAttribLocation(shaderId, "vcolor");
   textureLoc = glGetAttribLocation(shaderId, "vtex");
}

#pragma region VEC_AND_MATRIX_SETTERS
void Shader::SetInt(int _loc, int _val) const
{
   if (_loc != -1)
   {
      glUniform1i(_loc, _val);
   }
}

void Shader::SetFloat(int _loc, float _val) const
{
   if (_loc != -1)
   {
      glUniform1f(_loc, _val);
   }
}

void Shader::SetVec3(int _loc, const glm::vec3& _vec) const
{
   if (_loc != -1)
   {
      glUniform3f(_loc, _vec.x, _vec.y, _vec.z);
   }
}

void Shader::SetVec4(int _loc, const glm::vec4& _vec) const
{
   if (_loc != -1)
   {
      glUniform4f(_loc, _vec.x, _vec.y, _vec.z, _vec.w);
   }
}

void Shader::SetMatrix(int _loc, const glm::mat4& _matrix) const
{
   if (_loc != -1)
   {
      glUniformMatrix4fv(_loc, 1, false, value_ptr(_matrix));
   }
}
#pragma endregion

uint32_t Shader::GetId() const
{
   return shaderId;
}

const char* Shader::GetError()
{
   return error;
}

void Shader::Use() const
{
   glUseProgram(shaderId);
}

void Shader::SetupAttribs() const
{
   if (location != -1)
   {
      glEnableVertexAttribArray(location);
      glVertexAttribPointer(
         location, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const
         void*>(offsetof(Vertex, vertexPosition)));
   }

   if (colorLoc != -1)
   {
      glEnableVertexAttribArray(colorLoc);
      glVertexAttribPointer(
         colorLoc, 3, GL_FLOAT, false, sizeof(Vertex), reinterpret_cast<const
         void*>(offsetof(Vertex, vertexColor)));
   }

   if (textureLoc != -1)
   {
      glEnableVertexAttribArray(textureLoc);
      glVertexAttribPointer(
         textureLoc, 2, GL_INT, false, sizeof(Vertex), reinterpret_cast<const
         void*>(offsetof(Vertex, texture)));
   }
}

int Shader::GetLocation(const char* _name) const
{
   return glGetUniformLocation(shaderId, _name);
}

std::string Shader::ReadString(const std::string& _fileName)
{
   std::ifstream istream(_fileName.c_str(), std::ios_base::binary);
   std::stringstream sstream;
   sstream << istream.rdbuf();

   return sstream.str();
}

