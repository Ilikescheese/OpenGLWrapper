#include "ShaderProg.h"

OGL::ShaderProg::ShaderProg(const std::string &source,ShaderProgType type) {
	const char *src = OGL::loadFile(source).c_str();
	object = glCreateShaderProgramv((GLenum)type, 1, &src);
}

OGL::ShaderProg::~ShaderProg() {
	glDeleteShader(object);
}

