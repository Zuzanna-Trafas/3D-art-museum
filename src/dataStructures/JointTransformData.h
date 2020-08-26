//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_JOINTTRANSFORMDATA_H
#define MUZEUM_JOINTTRANSFORMDATA_H

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>

class JointTransformData {
public:
    std::string jointNameId;
    glm::mat4 jointLocalTransform;

    JointTransformData(std::string _jointNameId, glm::mat4 _jointLocalTransform);
};


#endif //MUZEUM_JOINTTRANSFORMDATA_H
