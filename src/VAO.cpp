//
// Created by ztrafas on 19.09.2020.
//

#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &id);
}

VAO::~VAO() {
    glDeleteVertexArrays(1, &id);
}

void VAO::AddLayout(VBO &_VBO, unsigned int index, unsigned int count, unsigned int stride, unsigned int offset) {
    Bind();
    _VBO.Bind();
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, count, GL_FLOAT, false, stride*sizeof(float), (const void*) (offset*sizeof(float)));
    Unbind();
}

void VAO::Bind() {
    glBindVertexArray(id);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}