//
// Created by ztrafas on 19.09.2020.
//

#include "Human.h"

Human::Human() {
}

Human::Human(VAO *_vao, EB *_ebo, Texture* _texture, ShaderProgram *sp) :  sp(sp) {
    vao[0] = _vao;
    ebo[0] = _ebo;
    texture[0] = _texture;
    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);
}

Human::~Human() {}

void Human::add(VAO* _vao, EB *_ebo, Texture* _texture, int index) {
    vao[index] = _vao;
    ebo[index] = _ebo;
    texture[index] = _texture;
}

void Human::drawHuman(glm::mat4 M) {
    M = glm::translate(M, position);
    M = glm::rotate(M, rotation.x, glm::vec3(1, 0, 0));
    M = glm::rotate(M, rotation.y, glm::vec3(0, 1, 0));
    M = glm::rotate(M, rotation.z, glm::vec3(0, 0, 1));
    M = glm::scale(M, scale);
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
    for (int i = 0; i < 8; i++) {
        if (i == 2) {
            continue;
        }
        vao[i]->Bind();
        ebo[i]->Bind();

        texture[i]->Bind(sp->u(texture[i]->uniform_name), 0, GL_TEXTURE0);

        glDrawElements(GL_TRIANGLES, ebo[i]->count, GL_UNSIGNED_INT, nullptr);
        vao[i]->Unbind();
        ebo[i]->Unbind();
        texture[i]->Unbind(GL_TEXTURE0);
    }
}