#pragma once
#include <glad/glad.h>
#include <string>

namespace OGL {
	class Shader
	{
		GLuint m_program;
		std::string m_loadFile(const char *path);
		void m_compile(GLuint shader);
	public:
		void use() const;
		void build(const char *vSource, const char *fSource);
		void destroy();
		Shader(const char *vShadPath, const char *fShadPath); // Load shader from path
		Shader() = default;
		Shader(Shader &) = delete;
	};
}