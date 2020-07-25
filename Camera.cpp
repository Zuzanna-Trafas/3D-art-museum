#include "Camera.h"
#include "constants.h"

Camera::Camera(glm::vec3 Pos, glm::vec3 Front, glm::vec3 Up) {
    cameraPos = Pos;
    cameraFront = Front;
    cameraUp = Up;
    yaw = 0;
    pitch = 0;
}

void Camera::processInput(GLFWwindow *window) {
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        const float cameraSpeed = CAMERA_SPEED * glfwGetTime();
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            cameraPos += cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            cameraPos -= cameraSpeed * cameraFront;
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
        cameraPos.y = 0.0f;
    }
}

void Camera::mouseCallback(GLFWwindow* window) {
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
        double xpos, ypos;
        glfwGetCursorPos(window, &ypos, &xpos);

        yaw = ypos * MOUSE_SPEED;
        pitch = -xpos * MOUSE_SPEED;

        if(pitch > 89.0f)
            pitch = 89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        glm::vec3 direction;
        direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
        direction.y = sin(glm::radians(pitch));
        direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
        cameraFront = glm::normalize(direction);
    }

}

glm::mat4 Camera::getView() {
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}