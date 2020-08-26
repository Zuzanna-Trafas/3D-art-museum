//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_MESHDATA_H
#define MUZEUM_MESHDATA_H

#include <vector>

class MeshData {
private:
    std::vector<float> vertices;
    std::vector<float> textureCoords;
    std::vector<float> normals;
    std::vector<int>  indices;
    std::vector<int> jointIds;
    std::vector<float> vertexWeights;
public:
    MeshData();
    MeshData(std::vector<float> _vertices, std::vector<float> _textureCoords, std::vector<float> _normals,
             std::vector<int> _indices, std::vector<int> _jointIds, std::vector<float> _vertexWeights);
    std::vector<float> getVertices();
    std::vector<float> getTextureCoords();
    std::vector<float> getNormals();
    std::vector<int> getIndices();
    std::vector<int> getJointIds();
    std::vector<float> getVertexWeights();
};


#endif //MUZEUM_MESHDATA_H
