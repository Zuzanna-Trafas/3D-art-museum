//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_KEYFRAMEDATA_H
#define MUZEUM_KEYFRAMEDATA_H

#include<vector>
#include "JointTransformData.h"

class KeyFrameData {
public:
    float time;
    std::vector<JointTransformData> jointTransforms;

    KeyFrameData(float _time);
    void addJointTransform(JointTransformData transform);
};


#endif //MUZEUM_KEYFRAMEDATA_H
