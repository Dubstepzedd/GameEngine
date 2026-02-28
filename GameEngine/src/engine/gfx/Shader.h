#pragma once  
#include <glad/glad.h>  
#include <string>  
#include <glm/glm.hpp>  
#include <vector>  
#include <optional>  
#include <variant> 
#include "engine/io/Asset.h"
#include "engine/gfx/geometry/Buffer.h"

using UniformValue = std::variant<  
   float,  
   glm::vec2,  
   glm::vec3,  
   glm::vec4,  
   glm::mat3,  
   glm::mat4 
>;  

struct ShaderUniform {  
   std::string name;  
   GLenum type;  
   int size;  
   int location;  
};  

struct ShaderProgramSource {  
   std::string vertexSrc;  
   std::string fragmentSrc;  
};  

class Shader : public Asset {  
public:  
   Shader(const std::string& path);  

   ~Shader() {  
       glDeleteProgram(m_ProgramId);  
   }  

   bool load() override;
   AssetType getType() const override { return AssetType::Shader; }

   GLuint getProgramId() const { return m_ProgramId; }  
   void setUniform(const std::string& name, const UniformValue& value);
   void setSamplerUniform(const std::string& name, int textureUnit) const;
   bool hasUniform(const std::string& name) const;  
   std::vector<ShaderUniform> getActiveUniforms() const;
   std::optional<GLenum> getUniformType(const std::string& name) const;
   
   void setLayout(BufferLayout layout) {
       m_BufferLayout = layout;
   }

   BufferLayout getLayout() const {
       return m_BufferLayout;
   }

private:  
   ShaderProgramSource parseShader(const std::string& path);  
   int compileShader(const unsigned int type, const std::string& src);  
   void createShader(const std::string& vertexSrc, const std::string& fragmentSrc);  
   bool isValidUniform(const int location, const std::string& name) const;  
   void setFloat4Uniform(const std::string& name, const glm::vec4 vector) const;
   void setFloat3Uniform(const std::string& name, const glm::vec3 vector) const;
   void setFloat2Uniforms(const std::string& name, const glm::vec2 vector) const;
   void setFloatUniform(const std::string& name, const GLfloat& number) const;
   void setMat4Uniform(const std::string& name, const glm::mat4 matrix, const bool transpose) const;
   void setMat3Uniform(const std::string& name, const glm::mat3 matrix, const bool transpose) const;

   std::vector<ShaderUniform> m_ActiveUniforms;  
   GLuint m_ProgramId = 0;  
   BufferLayout m_BufferLayout;
};
