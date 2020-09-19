//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_ANIMATEDMODELLOADER_H
#define MUZEUM_ANIMATEDMODELLOADER_H

#include "AnimatedModel.h"
#include "Vao.h"
#include "Joint.h"
#include "loaders/ColladaLoader.h"
#include "../res/dataStructures/AnimatedModelData.h"
#include "../res/dataStructures/JointData.h"
#include "../res/dataStructures/MeshData.h"
#include "../res/dataStructures/SkeletonData.h"
#include "../constants.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <string>


class AnimatedModelLoader {
    AnimatedModel loadEntity(std::string modelFile, std::string textureFile);
    AnimatedModelData loadData(std::string modelFile);
    GLuint loadTexture(std::string textureFile);
    Joint createJoints(JointData data);
    Vao createVao(MeshData data);
};


#endif //MUZEUM_ANIMATEDMODELLOADER_H
