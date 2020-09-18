//
// Created by ztrafas on 28.08.2020.
//

#ifndef MUZEUM_ANIMATEDMODELRENDERER_H
#define MUZEUM_ANIMATEDMODELRENDERER_H

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "AnimatedModel.h"

class AnimatedModelRenderer {
    void render(AnimatedModel entity);
};


#endif //MUZEUM_ANIMATEDMODELRENDERER_H
