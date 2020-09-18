//
// Created by ztrafas on 26.08.2020.
//

#include "AnimatedModelData.h"

AnimatedModelData::AnimatedModelData(MeshData _mesh, SkeletonData _joints) {
    joints = _joints;
    mesh = _mesh;
}
SkeletonData AnimatedModelData::getJointsData() {
    return joints;
}
MeshData AnimatedModelData::getMeshData() {
    return mesh;
}
