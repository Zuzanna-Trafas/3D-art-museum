//
// Created by ztrafas on 26.08.2020.
//

#include "JointTransformData.h"

JointTransformData::JointTransformData(std::string _jointNameId, glm::mat4 _jointLocalTransform) {
    jointNameId = _jointNameId;
    jointLocalTransform = _jointLocalTransform;
}