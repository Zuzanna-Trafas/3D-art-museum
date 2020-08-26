//
// Created by ztrafas on 26.08.2020.
//

#include "JointData.h"

JointData::JointData() {

}

JointData::JointData(int _id, std::string _nameId, glm::mat4 _bindLocalTransform) {
    id = _id;
    nameId = _nameId;
    bindLocalTransform = _bindLocalTransform;
}

void JointData::addChild(JointData child) {
    children.push_back(child);
}