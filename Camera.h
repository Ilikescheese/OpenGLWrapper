#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/mat4x4.hpp>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace OGL {
	class NMShader;
}

class Camera
{
	static inline void m_cursor(GLFWwindow *window, double xPos, double yPos);
	void m_calcDirs();
	bool m_firstMouse = true;
public:
	
	glm::vec3 position = { 0, 0, 3 };
	glm::vec3 front = { 0, 0, -1 };
	glm::vec3 upDir = { 0, 1, 0 };
	glm::vec3 up;
	glm::vec3 right;
	glm::vec3 dir;

	glm::mat4 proj = glm::mat4(1);
	glm::mat4 view = glm::mat4(1);
	glm::mat4 model = glm::mat4(1);

	float pitch = 45, yaw = -90, roll = 0;
	float prevCursX, prevCursY, cursXOffset, cursYOffset;
	float sensitivity = .1;
	float speed = 2.5;

	void update(OGL::NMShader &shader, GLFWwindow *window, float delta); //Set shader values
	Camera(GLFWwindow *window, unsigned wWidth, unsigned wHeight);
};

