//
// Created by ztrafas on 28.08.2020.
//

#include "KeyFrame.h"

KeyFrame::KeyFrame(float _timeStamp, std::map<std::string, JointTransform> jointKeyFrames) {
    timeStamp = _timeStamp;
    pose = jointKeyFrames;
}