//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_ANIMATIONDATA_H
#define MUZEUM_ANIMATIONDATA_H

#include "KeyFrameData.h"
#include <vector>

class AnimationData {
public:
    float lengthSeconds;
    std::vector<KeyFrameData> keyFrames;
    AnimationData(float _lengthSeconds, std::vector<KeyFrameData> _keyFrames);
};


#endif //MUZEUM_ANIMATIONDATA_H
