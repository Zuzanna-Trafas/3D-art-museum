//
// Created by ztrafas on 26.08.2020.
//

#include "AnimationData.h"

AnimationData::AnimationData(float _lengthSeconds, std::vector<KeyFrameData> _keyFrames) {
    lengthSeconds = _lengthSeconds;
    keyFrames = _keyFrames;
}
