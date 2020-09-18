//
// Created by ztrafas on 29.08.2020.
//

#ifndef MUZEUM_VAO_H
#define MUZEUM_VAO_H

#include "../constants.h"
#include "Vbo.h"
#include <vector>

class Vao {
private:
    std::vector<Vbo> dataVbos;
    Vbo indexVbo;
    int indexCount;
public:
    GLuint id;
    Vao();
    ~Vao();
    int getIndexCount() {return indexCount;}
    void bind();
    void unbind();
    void createIndexBuffer(std::vector<int> indices);
    void createAttributeFloat(int attribute, std::vector<float> data, int attrSize);
    void createAttributeInt(int attribute, std::vector<int> data, int attrSize);

};


#endif //MUZEUM_VAO_H
