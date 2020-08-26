//
// Created by ztrafas on 26.08.2020.
//

#include "MeshData.h"

MeshData::MeshData() {

}

MeshData::MeshData(std::vector<float> _vertices, std::vector<float> _textureCoords, std::vector<float> _normals,
std::vector<int> _indices, std::vector<int> _jointIds, std::vector<float> _vertexWeights) {
    vertices = _vertices;
    textureCoords = _textureCoords;
    normals = _normals;
    indices = _indices;
    jointIds = _jointIds;
    vertexWeights = _vertexWeights;
}

std::vector<float> MeshData::getVertices() {
    return vertices;
}

std::vector<float> MeshData::getTextureCoords() {
    return textureCoords;
}

std::vector<float> MeshData::getNormals() {
    return normals;
}

std::vector<int> MeshData::getIndices() {
    return indices;
}

std::vector<int> MeshData::getJointIds() {
    return jointIds;
}

std::vector<float> MeshData::getVertexWeights() {
    return vertexWeights;
}