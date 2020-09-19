//
// Created by ztrafas on 19.09.2020.
//

#ifndef MUZEUM_VBO_H
#define MUZEUM_VBO_H

#include <GL/glew.h>

class VBO {
private:
    GLuint id;
public:
    VBO(const void* data, unsigned int size);
    ~VBO();

    void Bind();
    void Unbind();
};


#endif //MUZEUM_VBO_H
