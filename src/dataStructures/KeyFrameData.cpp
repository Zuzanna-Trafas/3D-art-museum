//
// Created by ztrafas on 26.08.2020.
//

#include "KeyFrameData.h"

KeyFrameData::KeyFrameData(float _time) {
    time = _time;
}
void KeyFrameData::addJointTransform(JointTransformData transform) {
    jointTransforms.push_back(transform);
}