#include <Camera.h>
#include <glm/gtc/matrix_transform.hpp>

Camera::Camera(glm::vec3 position, glm::vec3 lookPos) : speed(0), deltaSpeed(4.5f), 
                                                        currentTime(0), lastTime(0), deltaTime(0), 
                                                        lastX(0), lastY(0),
                                                        yaw(0), pitch(0),
                                                        xpos(0), ypos(0), firstMouse(true)
{
	this->position = position;
	front = glm::normalize(lookPos - position);
	up = glm::vec3(0.0f, 1.0f, 0.0f);

    yaw = asin(front.x) * 3.14 / 180, pitch = asin(front.y) * 3.14 / 180;

	View = glm::lookAt(position, position + front, up);
}

glm::vec3 Camera::getPosition()
{
    return position;
}

glm::mat4 Camera::getViewMatrix()
{
    return View;
}

void Camera::Update(GLFWwindow* window)
{
    currentTime = glfwGetTime();
    deltaTime = currentTime - lastTime;
    lastTime = currentTime;

    CameraKeyboard(window);
    CameraMouse(window);

    View = glm::lookAt(position, position + front, up);
}

void Camera::CameraKeyboard(GLFWwindow* window)
{
    speed = deltaSpeed * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        position += speed * front;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        position -= speed * front;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        position -= glm::normalize(glm::cross(front, up)) * speed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        position += glm::normalize(glm::cross(front, up)) * speed;
}

void Camera::CameraMouse(GLFWwindow* window)
{
    float xoffset, yoffset, sensitivity;
    glm::vec3 direction;

    glfwGetCursorPos(window, &xpos, &ypos);

    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    xoffset = xpos - lastX;
    yoffset = lastY - ypos;
    lastX = xpos, lastY = ypos;

    sensitivity = 0.002f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw += xoffset;
    pitch += yoffset;

    if (pitch > 1.55f)
        pitch = 1.55f;
    if (pitch < -1.55f)
        pitch = -1.55f;

    direction.x = cos(yaw) * cos(pitch);
    direction.y = sin(pitch);
    direction.z = sin(yaw) * cos(pitch);
    front = glm::normalize(direction);
}

