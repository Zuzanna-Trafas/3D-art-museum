//
// Created by ztrafas on 27.08.2020.
//

#ifndef MUZEUM_COLLADALOADER_H
#define MUZEUM_COLLADALOADER_H

#include "../../res/dataStructures/AnimationData.h"
#include "../../res/dataStructures/AnimatedModelData.h"
#include "../../res/dataStructures/MeshData.h"
#include "../../res/dataStructures/SkeletonData.h"
#include "../../res/dataStructures/SkinningData.h"
#include "../rapidxml/rapidxml.hpp"
#include <string>


class ColladaLoader {
public:
    ColladaLoader() {}
    AnimatedModelData loadColladaModel(std::string colladaFile, int maxWeights);

};


#endif //MUZEUM_COLLADALOADER_H
