#pragma once
#include <glad/glad.h>
#include "loadFile.h"
//Objects encapsulating vertex shaders and fragment shaders
//To be used in conjunction with OGL::Shader
namespace OGL {
	enum class ShaderProgType {
		Vertex = GL_VERTEX_SHADER,
		Fragment = GL_FRAGMENT_SHADER
	};
	class ShaderProg {
	public:
		GLuint object;
		ShaderProg(const std::string &source,ShaderProgType type);
		ShaderProg(ShaderProg &) = delete;
		~ShaderProg();
	};
}