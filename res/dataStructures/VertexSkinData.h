//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_VERTEXSKINDATA_H
#define MUZEUM_VERTEXSKINDATA_H

#include <vector>
#include <algorithm>

class VertexSkinData {
public:
    std::vector<int> jointIds;
    std::vector<float> weights;

    void addJointEffect(int jointId, float weight);
    void limitJointNumber(int max);
    void fillEmptyWeights(int max);
    float saveTopWeights(std::vector<float> topWeightsArray);
    void refillWeightList(std::vector<float> topWeights, float total);
    void removeExcessJointIds(int max);
};


#endif //MUZEUM_VERTEXSKINDATA_H
