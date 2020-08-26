//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_ANIMATEDMODELDATA_H
#define MUZEUM_ANIMATEDMODELDATA_H

#include "SkeletonData.h"
#include "MeshData.h"

class AnimatedModelData {
private:
    SkeletonData joints;
    MeshData mesh;
public:
    AnimatedModelData(MeshData _mesh, SkeletonData _joints);
    SkeletonData getJointsData();
    MeshData getMeshData();
};


#endif //MUZEUM_ANIMATEDMODELDATA_H
