//
// Created by ztrafas on 29.08.2020.
//

#ifndef MUZEUM_VBO_H
#define MUZEUM_VBO_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class Vbo {
private:
    GLuint id;
    int type;
public:
    Vbo() {}
    Vbo(int type);
    ~Vbo();
    void bind();
    void unbind();
    void storeDataInt(std::vector<int> data);
    void storeDataFloat(std::vector<float> data);

};


#endif //MUZEUM_VBO_H
