#include "Camera.h"

#include "../NMShader.h"
#include <iostream>
static float curX = 0, curY = 0;
void Camera::m_cursor(GLFWwindow *window, double xPos, double yPos) {
	curX = xPos;
	curY = yPos;
}

void Camera::m_calcDirs() {
	if (m_firstMouse) {
		//Centre mouse if first time the mouse goes in window
		m_firstMouse = false;
		prevCursX = curX;
		prevCursY = curY;
	}
	//Calculate distance from previous pos
	cursXOffset = curX - prevCursX;
	cursYOffset = prevCursY - curY;
	//New previous cursor location
	prevCursX = curX;
	prevCursY = curY;
	//sensitivity
	cursXOffset *= sensitivity;
	cursYOffset *= sensitivity;
	//Set euler angles to work with
	pitch += cursYOffset;
	yaw += cursXOffset;
	//Lock pitch
	if (pitch >= 90)
		pitch = 89.99;
	if (pitch <= -90)
		pitch = -89.99;
	//Direction calcs
	dir.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
	dir.y = sin(glm::radians(pitch));
	dir.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

	//camera angle
	front = glm::normalize(dir);
	right = glm::normalize(glm::cross(front, upDir));
	up = glm::normalize(glm::cross(right, front));
}


void Camera::update(OGL::NMShader &shader, GLFWwindow *window, float delta) {
	float vel = speed * delta;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
		position += front * vel;
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
		position -= right * vel;
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
		position -= front * vel;
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
		position += right * vel;
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		position += up * vel;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
		position -= up * vel;
	m_calcDirs();
	view = glm::lookAt(position, position + front, up);
	shader.setMat4("proj", proj);
	shader.setMat4("view", view);
	shader.setMat4("model", model);
}

Camera::Camera(GLFWwindow *window, unsigned wWidth, unsigned wHeight) {
	//Lock the cursor
	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	//Callback for getting cursor coords
	glfwSetCursorPosCallback(window, m_cursor);

	proj = glm::perspective(glm::radians(60.0f), float(wWidth / wHeight), 0.1f, 100.0f);
	prevCursX = wWidth / 2;
	prevCursY = wHeight / 2;

	m_calcDirs();
}