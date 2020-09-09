#pragma once
#include <glad/glad.h>
namespace OGL {
	enum class RenderCmdType {
		basic,
		elements
	};
	struct RenderCmd {
		RenderCmdType type;
		GLenum mode = GL_TRIANGLES;
		GLuint first, count;
	};
}