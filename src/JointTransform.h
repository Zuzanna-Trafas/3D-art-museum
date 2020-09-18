//
// Created by ztrafas on 28.08.2020.
//

#ifndef MUZEUM_JOINTTRANSFORM_H
#define MUZEUM_JOINTTRANSFORM_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Quaternion.h"

class JointTransform {
private:
    // remember, this position and rotation are relative to the parent bone!
    glm::vec3 position;
    Quaternion rotation;
public:
    JointTransform();
    JointTransform(glm::vec3 _position, Quaternion _rotation);
    glm::mat4 getLocalTransform();
    JointTransform interpolate(JointTransform frameA, JointTransform frameB, float progression);
    glm::vec3 interpolate(glm::vec3 start, glm::vec3 end, float progression);
};


#endif //MUZEUM_JOINTTRANSFORM_H
