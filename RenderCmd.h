#pragma once
#include <glad/glad.h>
namespace OGL {
	enum RenderMode : GLenum {
		Triangles = GL_TRIANGLES,
		Points = GL_POINTS,
		Lines = GL_LINES
	};

	//Unsigned types
	enum Unsigns : GLuint {
		Int = GL_UNSIGNED_INT,
		Short = GL_UNSIGNED_SHORT,
		Byte = GL_UNSIGNED_BYTE
	};
	struct RenderCmd {
		RenderMode mode = RenderMode::Triangles;
		unsigned begin = 0;
		unsigned end = 0;
		unsigned instCount = 0;
		GLuint indicesType = Unsigns::Int;
	};
}