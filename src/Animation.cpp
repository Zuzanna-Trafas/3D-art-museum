//
// Created by ztrafas on 28.08.2020.
//

#include "Animation.h"

Animation::Animation() {}
Animation::Animation(float lengthInSeconds, std::vector<KeyFrame> frames) {
    length = lengthInSeconds;
    keyFrames = frames;
}