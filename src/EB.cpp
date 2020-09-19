//
// Created by ztrafas on 19.09.2020.
//

#include "EB.h"

EB::EB(unsigned int const* data, unsigned int count)
        : count(count) {
    glGenBuffers(1, &id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count*sizeof(unsigned int), data, GL_STATIC_DRAW);
}

EB::~EB() {
    glDeleteBuffers(1, &id);
}

void EB::Bind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void EB::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
