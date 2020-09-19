//
// Created by ztrafas on 19.09.2020.
//

#ifndef MUZEUM_VAO_H
#define MUZEUM_VAO_H

#include <GL/glew.h>
#include "VBO.h"

class VAO {
public:
    GLuint id;
    VAO();
    ~VAO();

    void AddLayout(VBO &_VBO, unsigned int index, unsigned int count, unsigned int stride, unsigned int offset);

    void Bind();
    void Unbind();
};


#endif //MUZEUM_VAO_H
