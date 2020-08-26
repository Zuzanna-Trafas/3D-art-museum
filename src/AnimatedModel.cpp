//
// Created by ztrafas on 22.08.2020.
//

#include "AnimatedModel.h"

AnimatedModel::AnimatedModel(Vao _model, GLuint _texture, Joint _rootJoint, int _jointCount) {
    model = _model;
    texture = _texture;
    rootJoint = _rootJoint;
    jointCount = _jointCount;
    animator = new Animator(this);
    rootJoint.calcInverseBindTransform(glm::mat4(1.0f));

}
Vao AnimatedModel::getModel() {
    return model;
}

GLuint AnimatedModel::getTexture() {
    return texture;
}

Joint AnimatedModel::getRootJoint() {
    return rootJoint;
}

AnimatedModel::~AnimatedModel() {
    glDeleteTextures(1,&texture);
    // delete model;
}

void AnimatedModel::doAnimation(Animation animation) {
    animator.doAnimation(animation);
}

void AnimatedModel::update() {
    animator.update();
}

std::vector<glm::mat4> AnimatedModel::getJointTransforms() {
    std::vector<glm::mat4> joinMatrices(jointCount, glm::mat4(1.0f));
    addJointsToArray(rootJoint, joinMatrices);
    return joinMatrices;
}
void AnimatedModel::addJointsToArray(Joint headJoint, std::vector<glm::mat4> joinMatrices) {
    joinMatrices[headJoint.id] = headJoint.getAnimatedTransform();
    for (Joint childJoint : headJoint.children) {
        addJointsToArray(childJoint, joinMatrices);
    }
}