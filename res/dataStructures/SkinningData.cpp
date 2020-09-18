//
// Created by ztrafas on 26.08.2020.
//

#include "SkinningData.h"

SkinningData::SkinningData(std::vector<std::string> _jointOrder, std::vector<VertexSkinData> _verticesSkinData) {
    jointOrder = _jointOrder;
    verticesSkinData = _verticesSkinData;
}