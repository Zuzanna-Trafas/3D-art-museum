
#ifndef EN_SZKIELET02_LIN_CAMERA_H
#define EN_SZKIELET02_LIN_CAMERA_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Camera {
private:
    glm::vec3 cameraPos;
    glm::vec3 cameraFront;
    glm::vec3 cameraUp;
    float yaw;
    float pitch;
public:
    Camera(glm::vec3 Pos, glm::vec3 Front, glm::vec3 Up);
    void move(glm::vec3 newPos);
    void processInput(GLFWwindow *window);
    void mouseCallback(GLFWwindow* window);
    glm::mat4 getView();
};


#endif
