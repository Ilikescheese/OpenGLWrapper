#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
#include "VAObj.h"
#include "Initializer.h"
using namespace OGL;

void errCallback(int, const char *message) {
	std::cerr << "GLFW error:" << message << '\n';
}

static void APIENTRY debugCallbackGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar *message, const void *userParam) {
	std::cerr << "-------------OpenGL message\n";
	std::cerr << message;
	switch (source)
	{
	case GL_DEBUG_SOURCE_API:             std::cerr << "Where? API\n";								break;
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM:   std::cerr << "Where? Window System\n";					break;
	case GL_DEBUG_SOURCE_SHADER_COMPILER: std::cerr << "Where? Shader Compiler\n";					break;
	case GL_DEBUG_SOURCE_THIRD_PARTY:     std::cerr << "Where? Third Party\n";						break;
	case GL_DEBUG_SOURCE_APPLICATION:     std::cerr << "Where? Application\n";						break;
	case GL_DEBUG_SOURCE_OTHER:           std::cerr << "Where? Other\n";							break;
	}
	switch (type) {
	case GL_INVALID_ENUM:                  std::cerr << "Type: GL_LINVALID_ENUM\n";					break;
	case GL_INVALID_VALUE:                 std::cerr << "Type: GL_INVALID_VALUE\n";					break;
	case GL_INVALID_OPERATION:             std::cerr << "Type: GL_INVALID_OPERATION\n";				break;
	case GL_OUT_OF_MEMORY:                 std::cerr << "Type: GL_OUT_OF_MEMORY\n";					break;
	case GL_INVALID_FRAMEBUFFER_OPERATION: std::cerr << "Type: GL_INVALID_FRAMEBUFFER_OPERATION\n";	break;
	default:							   std::cerr << "Type: code=" << type << '\n';				break;
	}
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_HIGH:         std::cerr << "Severity: high\n";							break;
	case GL_DEBUG_SEVERITY_MEDIUM:       std::cerr << "Severity: medium\n";							break;
	case GL_DEBUG_SEVERITY_LOW:          std::cerr << "Severity: low\n";							break;
	case GL_DEBUG_SEVERITY_NOTIFICATION: std::cerr << "Severity: notification\n";					break;
	}
}

int main() {
	//OpenGL setup
	glfwSetErrorCallback(errCallback);
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(800, 600, "Wrapper", nullptr, nullptr);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwMakeContextCurrent(window);
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cerr << "Failed to load GLAD!\n";

	glDebugMessageCallback(debugCallbackGL, nullptr);
	glEnable(GL_DEBUG_OUTPUT);
	glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	//Init code for OGL wrapper
	Initializer init;

	Shader red("res/a.vert", "res/a.frag");
	std::vector<float> vertices = {
		0.5f, 0.5f, 0.0f,  // top right
		0.5f, -0.5f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  // bottom left
		-0.5f, 0.5f, 0.0f   // top left 
	};

	std::vector<unsigned> indices = {  // note that we start from 0!
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
<<<<<<< Updated upstream
	VAObj triangle(vertices, indices, { { 3 } });
=======
	VAObj triangle(vertices,indices, { {3} });
	
	red.use();
>>>>>>> Stashed changes

	red.use();
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4, 0.4, 0.4, 1);

		triangle.use();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	red.destroy();
	return 0;
}