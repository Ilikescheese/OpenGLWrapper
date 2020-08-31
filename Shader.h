#pragma once
#include <glad/glad.h>
class Shader
{
	GLuint program;
public:
	void loadFromSrc(const char *code); // Create shader from glsl directly
	void destroy();
	Shader(const char *path);
	Shader(Shader &) = delete;
};

