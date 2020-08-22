#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Joint.h"


Joint::Joint(int _id, std::string _name, glm::mat4 _bindLocalTransform) {
    id = _id;
    name = _name;
    localBindTransform = _bindLocalTransform;
}

void Joint::addChild(Joint child) {
    children.push_back(child);
}

glm::mat4 Joint::getAnimatedTransform() {
    return animatedTransform;
}

void Joint::setAnimationTransform(glm::mat4 animationTransform) {
    animatedTransform = animationTransform;
}

glm::mat4 Joint::getInverseBindTransform() {
    return inverseBindTransform;
}
void Joint::calcInverseBindTransform(glm::mat4 parentBindTransform) {
    glm::mat4 bindTransform = parentBindTransform * localBindTransform;
    inverseBindTransform = glm::inverse(bindTransform);
    for (Joint child : children) {
        child.calcInverseBindTransform(bindTransform);
    }
}