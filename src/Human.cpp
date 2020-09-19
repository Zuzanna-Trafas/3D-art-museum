//
// Created by ztrafas on 19.09.2020.
//

#include "Human.h"

Human::Human() {
    vao = nullptr;
    ebo = nullptr;
    sp = nullptr;
}

Human::Human(VAO *vao, EB *ebo, ShaderProgram *sp) :  vao(vao), ebo(ebo), sp(sp) {
    position = glm::vec3(0, 0, 0);
    rotation = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);
}

Human::~Human() {}

void Human::drawHuman(glm::mat4 M) {
    M = glm::translate(M, position);
    M = glm::rotate(M, rotation.x, glm::vec3(1, 0, 0));
    M = glm::rotate(M, rotation.y, glm::vec3(0, 1, 0));
    M = glm::rotate(M, rotation.z, glm::vec3(0, 0, 1));
    M = glm::scale(M, scale);
    glUniformMatrix4fv(sp->u("M"), 1, false, glm::value_ptr(M));
    vao->Bind();
    ebo->Bind();

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glEnableVertexAttribArray(4);
    glUniform1i(4, 0);

    glDrawElements(GL_TRIANGLES, ebo->count, GL_UNSIGNED_INT, nullptr);
    vao->Unbind();
    ebo->Unbind();

    glDisableVertexAttribArray(4);
}