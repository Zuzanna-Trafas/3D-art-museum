//
// Created by ztrafas on 28.08.2020.
//

#ifndef MUZEUM_ANIMATION_H
#define MUZEUM_ANIMATION_H

#include "KeyFrame.h"
#include <vector>

class Animation {
private:
    float length;
    std::vector<KeyFrame> keyFrames;

public:
    Animation();
    Animation(float lengthInSeconds, std::vector<KeyFrame> frames);
    float getLength() {return length;}
    std::vector<KeyFrame> getKeyFrames() {return keyFrames;}


};


#endif //MUZEUM_ANIMATION_H
