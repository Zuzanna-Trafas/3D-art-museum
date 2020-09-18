//
// Created by ztrafas on 26.08.2020.
//

#include "Vertex.h"

Vertex::Vertex() {

}

Vertex::Vertex(int _index, glm::vec3 _position, VertexSkinData _weightsData) {
    textureIndex = NO_INDEX;
    normalIndex = NO_INDEX;
    averagedTangent = glm::vec3(0.0f,0.0f,0.0f);
    index = _index;
    weightsData = _weightsData;
    position = _position;
    length = position.length();
}

void Vertex::addTangent(glm::vec3 _tangent) {
    tangents.push_back(_tangent);
}

void Vertex::averageTangents() {
    if (tangents.empty()) {
        return;
    }
    for (glm::vec3 tangent : tangents) {
        averagedTangent = averagedTangent + tangent;
    }
    glm::normalize(averagedTangent);
}

bool Vertex::isSet() {
    return textureIndex != NO_INDEX && normalIndex != NO_INDEX;
}

bool Vertex::hasSameTextureAndNormal(int textureIndexOther,int normalIndexOther) {
    return textureIndexOther==textureIndex && normalIndexOther==normalIndex;
}

void Vertex::setTextureIndex(int _textureIndex) {
    textureIndex = _textureIndex;
}

void Vertex::setNormalIndex(int _normalIndex) {
    normalIndex = _normalIndex;
}

void Vertex::setDuplicateVertex(Vertex _duplicateVertex) {
    *duplicateVertex = _duplicateVertex;
}