#ifndef MUZEUM_JOINT_H
#define MUZEUM_JOINT_H
#include <iostream>
#include <vector>

class Joint {
private:
    glm::mat4 animatedTransform = glm::mat4(1.0f);
    glm::mat4 localBindTransform;
    glm::mat4 inverseBindTransform = glm::mat4(1.0f);
public:
    int id;
    std::string name;
    std::vector<Joint> children;
    Joint(int index, std::string name, glm::mat4 bindLocalTransform);
    void addChild(Joint child);
    glm::mat4 getAnimatedTransform();
    void setAnimationTransform(glm::mat4 animationTransform);
    glm::mat4 getInverseBindTransform();
    void calcInverseBindTransform(glm::mat4 parentBindTransform);


};


#endif //MUZEUM_JOINT_H
