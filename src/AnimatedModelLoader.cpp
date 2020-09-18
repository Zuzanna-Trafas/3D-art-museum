//
// Created by ztrafas on 26.08.2020.
//

#include "AnimatedModelLoader.h"
#include "lodepng.h"


AnimatedModel AnimatedModelLoader::loadEntity(std::string modelFile, std::string textureFile) {
    ColladaLoader colladaLoader = ColladaLoader();
    AnimatedModelData entityData = colladaLoader.loadColladaModel(modelFile, MAX_WEIGHTS);
    Vao model = createVao(entityData.getMeshData());
    GLuint texture = loadTexture(textureFile);
    SkeletonData skeletonData = entityData.getJointsData();
    Joint headJoint = createJoints(skeletonData.headJoint);
    return AnimatedModel(model, texture, headJoint, skeletonData.jointCount);
}

GLuint AnimatedModelLoader::loadTexture(std::string textureFile) {
    GLuint tex;
    glActiveTexture(GL_TEXTURE0);
    //Read into computers memory
    std::vector<unsigned char> image; //Allocate memory
    unsigned width, height; //Variables for image size
    //Read the image
    unsigned error = lodepng::decode(image, width, height, textureFile);
    //Import to graphics card memory
    glGenTextures(1,&tex); //Initialize one handle
    glBindTexture(GL_TEXTURE_2D, tex); //Activate handle
    //Copy image to graphics cards memory represented by the active handle
    glTexImage2D(GL_TEXTURE_2D, 0, 4, width, height, 0,
                 GL_RGBA, GL_UNSIGNED_BYTE, (unsigned char*) image.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    return tex;
}

Joint AnimatedModelLoader::createJoints(JointData data) {
    Joint joint = Joint(data.id, data.nameId, data.bindLocalTransform);
    for (JointData child : data.children) {
        joint.addChild(createJoints(child));
    }
    return joint;
}

Vao AnimatedModelLoader::createVao(MeshData data) {
    Vao vao = Vao();
    vao.bind();
    vao.createIndexBuffer(data.getIndices());
    vao.createAttributeFloat(0, data.getVertices(), 3);
    vao.createAttributeFloat(1, data.getTextureCoords(), 2);
    vao.createAttributeFloat(2, data.getNormals(), 3);
    vao.createAttributeInt(3, data.getJointIds(), 3);
    vao.createAttributeFloat(4, data.getVertexWeights(), 3);
    vao.unbind();
    return vao;
}
