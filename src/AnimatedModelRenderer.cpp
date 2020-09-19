//
// Created by ztrafas on 28.08.2020.
//

#include "AnimatedModelRenderer.h"

void AnimatedModelRenderer::render(AnimatedModel entity) {

    std::vector<GLuint> attrib{ 0, 1, 2, 3, 4 };
    entity.getModel().bind(attrib);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, entity.getTexture());

    glDrawArrays(GL_TRIANGLES, 0, entity.getModel().getIndexCount());

    entity.getModel().unbind(attrib);
}