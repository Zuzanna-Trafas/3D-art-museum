#include "Camera.h"
#include "constants.h"

Camera::Camera(glm::vec3 Pos, glm::vec3 Front, glm::vec3 Up) {
    cameraPos = Pos;
    cameraFront = Front;
    cameraUp = Up;
    yaw = 0;
    pitch = 0;
}

void Camera::move(glm::vec3 newPos) {
    // check if not going beyond walls
    if (newPos.x > 72 || newPos.x < -72) return;
    if (newPos.z > 72 || newPos.z < -72) return;
    if (newPos.x < 17 && newPos.x > -17) {
        if (newPos.z > 47.5 || (newPos.z < 42.5 && newPos.z > 42.5)) return;
        if (newPos.z < -47.5 || (newPos.z > -42.5 && newPos.z < 42.5)) return;
    }
    if (newPos.z < 17 && newPos.z > -17) {
        if (newPos.x > 47.5 || (newPos.x < 42.5 && newPos.x > -42.5)) return;
        if (newPos.x < -47.5 || (newPos.x > -42.5 && newPos.x < 42.5)) return;
    }
    // if not, move
    cameraPos = newPos;
}

void Camera::processInput(GLFWwindow *window) {
    if (glfwGetWindowAttrib(window, GLFW_FOCUSED)) {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
            glfwSetWindowShouldClose(window, true);
        const float cameraSpeed = CAMERA_SPEED * glfwGetTime();
        if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
            move(cameraPos + cameraSpeed * cameraFront);
        if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
            move(cameraPos - cameraSpeed * cameraFront);
        if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
            move(cameraPos - glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
        if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
            move(cameraPos + glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
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
    //printf("x: %f y: %f z: %f\n", cameraPos.x, cameraPos.y, cameraPos.z);
    glm::mat4 view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
    return view;
}