//
// Created by ztrafas on 29.08.2020.
//

#include "Vbo.h"

Vbo::Vbo(int _type) {
    type = _type;
    glGenBuffers(1, &id);
}

Vbo::~Vbo() {
    glDeleteBuffers(1, &id);
}

void Vbo::bind() {
    glBindBuffer(type, id);
}

void Vbo::unbind() {
    glBindBuffer(type, 0);
}

void Vbo::storeDataFloat(std::vector<float> data) {
    int size = data.size();
    glBufferData(type, size* sizeof(float), data.data(), GL_STATIC_DRAW);
}

void Vbo::storeDataInt(std::vector<int> data) {
    int size = data.size();
    glBufferData(type, size* sizeof(int), data.data(), GL_STATIC_DRAW);
}
