#ifndef MUZEUM_JOINT_H
#define MUZEUM_JOINT_H

#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Joint {
private:
    glm::mat4 animatedTransform;
    glm::mat4 localBindTransform;
    glm::mat4 inverseBindTransform;
public:
    int id;
    std::string name;
    std::vector<Joint> children;
    Joint();
    Joint(int _id, std::string _name, glm::mat4 _bindLocalTransform);
    void addChild(Joint child);
    glm::mat4 getAnimatedTransform();
    void setAnimationTransform(glm::mat4 animationTransform);
    glm::mat4 getInverseBindTransform();
    void calcInverseBindTransform(glm::mat4 parentBindTransform);
};


#endif //MUZEUM_JOINT_H
