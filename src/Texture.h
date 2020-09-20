//
// Created by ztrafas on 20.09.2020.
//

#ifndef MUZEUM_TEXTURE_H
#define MUZEUM_TEXTURE_H

#include <GL/glew.h>
#include <iostream>
#include <vector>


class Texture {
public:
    GLuint id;
    const char* uniform_name;
    Texture() {};
    Texture(const char* filename, const char* uniform_name);
    ~Texture();
    void Bind(unsigned int index, unsigned int unit_id, unsigned int texture_unit);
    void Unbind(unsigned int texture_unit);
};


#endif //MUZEUM_TEXTURE_H
