//
// Created by ztrafas on 22.08.2020.
//

#ifndef MUZEUM_ANIMATEDMODEL_H
#define MUZEUM_ANIMATEDMODEL_H

#include "Joint.h"
#include "Animator.h"
#include "Animation.h"
#include "Vao.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

class AnimatedModel {
private:
    // skin
    Vao model;
    GLuint texture;

    //skeleton
    Joint rootJoint;
    int jointCount;

    Animator animator;

public:
    AnimatedModel() {}
    AnimatedModel(Vao _model, GLuint _texture, Joint _rootJoint, int jointCount);
    virtual ~AnimatedModel();
    Vao getModel();
    GLuint getTexture();
    Joint getRootJoint();
    void doAnimation(Animation animation);
    void update();
    std::vector<glm::mat4> getJointTransforms();
    void addJointsToArray(Joint headJoint, std::vector<glm::mat4> joinMatrices);
};


#endif //MUZEUM_ANIMATEDMODEL_H
