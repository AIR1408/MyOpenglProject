#ifndef CAMERA_H
#define CAMERA_H

#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW\glfw3.h>

class Camera
{
public:
	Camera(glm::vec3 position, glm::vec3 lookDirection);

	glm::vec3 getPosition();
	glm::mat4 getViewMatrix();

	void Update(GLFWwindow* window);

private:
	glm::vec3 position, front, up;

	float
		speed, deltaSpeed = 4.5,
		currentTime, lastTime, deltaTime,
		lastX, lastY,
		yaw, pitch;

	double xpos, ypos;

	bool firstMouse = true;

	glm::mat4 View;

	void CameraKeyboard(GLFWwindow* window);
	void CameraMouse(GLFWwindow* window);

	//void CameraInit();
};

#endif // !CAMERA_H
