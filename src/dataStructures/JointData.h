//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_JOINTDATA_H
#define MUZEUM_JOINTDATA_H

#include <vector>
#include <string>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class JointData {
public:
    int id;
    std::string nameId;
    glm::mat4 bindLocalTransform;

    std::vector<JointData> children;

    JointData();
    JointData(int _id, std::string _nameId, glm::mat4 _bindLocalTransform);
    void addChild(JointData child);
};


#endif //MUZEUM_JOINTDATA_H
