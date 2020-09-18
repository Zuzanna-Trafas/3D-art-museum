//
// Created by ztrafas on 26.08.2020.
//

#include "SkeletonData.h"


SkeletonData::SkeletonData() {

}

SkeletonData::SkeletonData(int _jointCount, JointData _headJoint) {
    jointCount = _jointCount;
    headJoint = _headJoint;
}