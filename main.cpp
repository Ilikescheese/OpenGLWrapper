#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
void errCallback(int, const char *message) {
	std::cerr << "GLFW error:" << message << '\n';
}

int main() {
	glfwSetErrorCallback(errCallback);
	glfwInit();
	GLFWwindow *window = glfwCreateWindow(800, 600, "Wrapper", nullptr, nullptr);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 5);
	glfwMakeContextCurrent(window);




	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		std::cerr << "Failed to load GLAD!\n";
	while (!glfwWindowShouldClose(window)) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.4, 0.4, 0.4, 1);

		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}