#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

#include "Shader.h"
void errCallback(int, const char *message) {
	std::cerr << "GLFW error:" << message << '\n';
}

static void APIENTRY debugCallbackGL(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length,
	const GLchar *message, const void *userParam) {
	std::cerr << "-----GL message---------------\n";
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
	std::cerr << message;
	std::cerr << "------------------------------\n";
}


int main() {
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cerr << "Failed to load GLAD!\n";
	glfwSetErrorCallback(errCallback);
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(800, 600, "Wrapper", nullptr, nullptr);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwMakeContextCurrent(window);
	glDebugMessageCallback(debugCallbackGL, nullptr);
	Shader red("res/a.vert", "res/a.frag");
	GLuint vertices[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};
	GLuint triangle;
	glGenBuffers(1, &triangle);
	glBindBuffer(GL_ARRAY_BUFFER, triangle);
	glBufferData(GL_ARRAY_BUFFER, 9 * sizeof(float), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	glEnableVertexAttribArray(0);

	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4, 0.4, 0.4, 1);

		glDrawArrays(GL_TRIANGLES, 0, 3);
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();

	glDeleteBuffers(1, &triangle);
	red.destroy();
	return 0;
}