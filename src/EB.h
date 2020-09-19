//
// Created by ztrafas on 19.09.2020.
//

#ifndef MUZEUM_EB_H
#define MUZEUM_EB_H

#include <GL/glew.h>

class EB {
public:
    GLuint id;
    unsigned int count;
    EB(unsigned int const* data, unsigned int count);
    ~EB();

    void Bind();
    void Unbind();
};


#endif //MUZEUM_EB_H
