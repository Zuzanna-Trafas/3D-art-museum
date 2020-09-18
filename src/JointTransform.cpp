//
// Created by ztrafas on 28.08.2020.
//

#include "JointTransform.h"

JointTransform::JointTransform() {}

JointTransform::JointTransform(glm::vec3 _position, Quaternion _rotation) {
    position = _position;
    rotation = _rotation;
}
glm::mat4 JointTransform::getLocalTransform() {
    glm::mat4 matrix = glm::translate(glm::mat4(1.0f), position);
    matrix = matrix * rotation.toRotationMatrix();
    return matrix;
}
JointTransform JointTransform::interpolate(JointTransform frameA, JointTransform frameB, float progression) {
    glm::vec3 pos = interpolate(frameA.position, frameB.position, progression);
    Quaternion rot;
    rot = rot.interpolate(frameA.rotation, frameB.rotation, progression);
    return JointTransform(pos, rot);
}

glm::vec3 JointTransform::interpolate(glm::vec3 start, glm::vec3 end, float progression) {
    float x = start.x + (end.x - start.x) * progression;
    float y = start.y + (end.y - start.y) * progression;
    float z = start.z + (end.z - start.z) * progression;
    return glm::vec3(x, y, z);
}