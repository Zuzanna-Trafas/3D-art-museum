//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_SKINNINGDATA_H
#define MUZEUM_SKINNINGDATA_H

#include <vector>
#include <string>
#include "VertexSkinData.h"

class SkinningData {
public:
    std::vector<std::string> jointOrder;
    std::vector<VertexSkinData> verticesSkinData;
    SkinningData(std::vector<std::string> _jointOrder, std::vector<VertexSkinData> verticesSkinData);
};


#endif //MUZEUM_SKINNINGDATA_H
