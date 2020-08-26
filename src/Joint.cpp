#include "Joint.h"


Joint::Joint() {

}

Joint::Joint(int _id, std::string _name, glm::mat4 _bindLocalTransform) {
    id = _id;
    name = _name;
    localBindTransform = _bindLocalTransform;
    animatedTransform = glm::mat4(1.0f);
    inverseBindTransform = glm::mat4(1.0f);
    children.resize(1000);
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