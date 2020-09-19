//
// Created by ztrafas on 19.09.2020.
//

#ifndef MUZEUM_HUMAN_H
#define MUZEUM_HUMAN_H

#include "VAO.h"
#include "VBO.h"
#include "EB.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "shaderprogram.h"

class Human {
public:
    Human();
    Human(VAO* vao, EB *ebo, ShaderProgram *sp);
    VAO *vao;
    EB *ebo;
    ShaderProgram *sp;
    GLuint texture;
    glm::vec3 position;
    glm::vec3 rotation;
    glm::vec3 scale;

    ~Human();
    void drawHuman(glm::mat4 M);
};


#endif //MUZEUM_HUMAN_H
