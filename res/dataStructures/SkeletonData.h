//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_SKELETONDATA_H
#define MUZEUM_SKELETONDATA_H

#include "JointData.h"

class SkeletonData {
public:
    int jointCount;
    JointData headJoint;
    SkeletonData();
    SkeletonData(int _jointCount, JointData _headJoint);
};


#endif //MUZEUM_SKELETONDATA_H
