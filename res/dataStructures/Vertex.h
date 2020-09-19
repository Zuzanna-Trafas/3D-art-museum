//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_VERTEX_H
#define MUZEUM_VERTEX_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "VertexSkinData.h"

class Vertex {
public:
    int NO_INDEX = -1;

    glm::vec3 position;
    int textureIndex;
    int normalIndex;
    Vertex *duplicateVertex;
    int index;
    float length;
    std::vector<glm::vec3> tangents;
    glm::vec3 averagedTangent;

    VertexSkinData weightsData;

    Vertex();
    Vertex(int _index, glm::vec3 _position, VertexSkinData _weightsData);
    glm::vec3 getPosition() {return position;}
    int getTextureIndex() {return textureIndex;}
    int getNormalIndex() {return normalIndex;}
    Vertex getDuplicateVertex() {return *duplicateVertex;}
    int getIndex() {return index;}
    float getLength() {return length;}
    std::vector<glm::vec3> getTangents() {return tangents;}
    glm::vec3 getAveragedTangent() {return averagedTangent;}
    VertexSkinData getWeightsData() {return weightsData;}
    void addTangent(glm::vec3 _tangent);
    void averageTangents();
    bool isSet();
    bool hasSameTextureAndNormal(int textureIndexOther,int normalIndexOther);
    void setTextureIndex(int _textureIndex);
    void setNormalIndex(int _normalIndex);
    void setDuplicateVertex(Vertex duplicateVertex);
};


#endif //MUZEUM_VERTEX_H
