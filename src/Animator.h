//
// Created by ztrafas on 26.08.2020.
//

#ifndef MUZEUM_ANIMATOR_H
#define MUZEUM_ANIMATOR_H

#include "Animation.h"
#include "Joint.h"
#include "KeyFrame.h"
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <map>
#include <string>
#include <vector>
#include <math.h>

class Animator {
private:
    // AnimatedModel entity;
    Animation currentAnimation;
    Joint rootJoint;
    float animationTime = 0;
    bool currentAnimationInitialized;

public:
    Animator();
    // Animator(AnimatedModel _entity);
    Animator(Joint _rootJoint);
    void doAnimation(Animation animation);
    void update();
    void increaseAnimationTime();
    std::map<std::string, glm::mat4> calculateCurrentAnimationPose();
    void applyPoseToJoints(std::map<std::string, glm::mat4> currentPose, Joint joint, glm::mat4 parentTransform);
    std::vector<KeyFrame> getPreviousAndNextFrames();
    float calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame);
    std::map<std::string, glm::mat4> interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression);
};


#endif //MUZEUM_ANIMATOR_H
