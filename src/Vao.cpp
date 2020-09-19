//
// Created by ztrafas on 29.08.2020.
//

#include "Vao.h"

Vao::Vao() {
    glGenVertexArrays(1, &id);
}

Vao::~Vao() {
    glDeleteVertexArrays(1, &id);
    for(Vbo vbo : dataVbos){
        delete &vbo;
    }
    delete &indexVbo;
}

void Vao::bind(std::vector<GLuint> attributes) {
    for (int i : attributes) {
        glBindVertexArray(i);
    }
}
void Vao::unbind(std::vector<GLuint> attributes) {
    for (int i : attributes) {
        glBindVertexArray(i, 0);
    }
}

void Vao::createIndexBuffer(std::vector<int> indices) {
    indexVbo = Vbo(GL_ELEMENT_ARRAY_BUFFER);
    indexVbo.bind();
    indexVbo.storeDataInt(indices);
    indexCount = indices.size();
}

void Vao::createAttributeFloat(int attribute, std::vector<float> data, int attrSize) {
    Vbo dataVbo = Vbo(GL_ARRAY_BUFFER);
    dataVbo.bind();
    dataVbo.storeDataFloat(data);
    glVertexAttribPointer(attribute, attrSize, GL_FLOAT, false, attrSize * sizeof(float), 0);
    dataVbo.unbind();
    dataVbos.push_back(dataVbo);
}

void Vao::createAttributeInt(int attribute, std::vector<int> data, int attrSize) {
    Vbo dataVbo = Vbo(GL_ARRAY_BUFFER);
    dataVbo.bind();
    dataVbo.storeDataInt(data);
    glVertexAttribPointer(attribute, attrSize, GL_INT, false, attrSize * sizeof(int), 0); //TODO glVertexAttribIPointer
    dataVbo.unbind();
    dataVbos.push_back(dataVbo);
}
