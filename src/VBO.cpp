//
// Created by ztrafas on 19.09.2020.
//

#include "VBO.h"

VBO::VBO(const void* data, unsigned int size) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ARRAY_BUFFER, id);
    glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), data, GL_STATIC_DRAW);
}

VBO::~VBO() {
    glDeleteBuffers(1, &id);
}

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}