#pragma once
#include <glad/glad.h>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>

/*
Non modular shader

A traditional monolithic shader program, fragment and vertex shaders are grouped together
*/
namespace OGL {
	class NMShader
	{
		GLuint m_program;
		void m_compile(GLuint shader);
	public:
		virtual void use() const;
		void build(const char *vSource, const char *fSource); // Overwrites previous shader handles, if the shader changes frequently then use OGL::Shader
		void destroy();
		void setMat4(const char *parameter, const glm::mat4 &matrix);
		void setVec2(const char *parameter, const glm::vec2 &vector);
		void setVec3(const char *parameter, const glm::vec3 &vector);
		void setVec4(const char *parameter, const glm::vec4 &vector);
		void setInt(const char *parameter, const GLint &integer);
		void setHandle(const char *parameter, const GLuint64 &value);
		NMShader(const char *vShadPath, const char *fShadPath); // Load shader from path
		NMShader() = default;
		NMShader(NMShader &) = delete;
		NMShader(NMShader &&rhs) noexcept;
	};
}