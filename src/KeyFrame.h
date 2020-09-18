//
// Created by ztrafas on 28.08.2020.
//

#ifndef MUZEUM_KEYFRAME_H
#define MUZEUM_KEYFRAME_H

#include <map>
#include <string>
#include "JointTransform.h"


class KeyFrame {
private:
    float timeStamp;
    std::map<std::string, JointTransform> pose;

public:
    KeyFrame();
    KeyFrame(float _timeStamp, std::map<std::string, JointTransform> jointKeyFrames);
    float getTimeStamp() {return timeStamp;}
    std::map<std::string, JointTransform> getJointKeyFrames() {return pose;}

};


#endif //MUZEUM_KEYFRAME_H
