//
// Created by ztrafas on 26.08.2020.
//

#include "Animator.h"

Animator::Animator() {}

//Animator::Animator(AnimatedModel _entity) {
//    entity = _entity;
//}

Animator::Animator(Joint _rootJoint) {
    rootJoint = _rootJoint;
}

void Animator::update() {
    if (!currentAnimationInitialized) {
        return;
    }
    increaseAnimationTime();
    std::map<std::string, glm::mat4> currentPose = calculateCurrentAnimationPose();
    applyPoseToJoints(currentPose, rootJoint, glm::mat4(1.0f));
}

void Animator::increaseAnimationTime() {
    animationTime += glfwGetTime(); // TODO
    if (animationTime > currentAnimation.getLength()) {
        animationTime = fmod(animationTime, currentAnimation.getLength());
    }
}

std::map<std::string, glm::mat4> Animator::calculateCurrentAnimationPose() {
    std::vector<KeyFrame> frames = getPreviousAndNextFrames();
    float progression = calculateProgression(frames[0], frames[1]);
    return interpolatePoses(frames[0], frames[1], progression);
}

void Animator::applyPoseToJoints(std::map<std::string, glm::mat4> currentPose, Joint joint, glm::mat4 parentTransform) {
    glm::mat4 currentLocalTransform = currentPose.at(joint.name);
    glm::mat4 currentTransform = parentTransform * currentLocalTransform;
    for (Joint childJoint : joint.children) {
        applyPoseToJoints(currentPose, childJoint, currentTransform);
    }
    currentTransform = currentTransform * joint.getInverseBindTransform();
    joint.setAnimationTransform(currentTransform);
}

std::vector<KeyFrame> Animator::getPreviousAndNextFrames() {
    std::vector<KeyFrame> allFrames = currentAnimation.getKeyFrames();
    KeyFrame previousFrame = allFrames[0];
    KeyFrame nextFrame = allFrames[0];
    for (int i = 1; i < allFrames.size() ; i++) {
        nextFrame = allFrames[i];
        if (nextFrame.getTimeStamp() > animationTime) {
            break;
        }
        previousFrame = allFrames[i];
    }
    std::vector<KeyFrame> returnedKeyFrames = {previousFrame, nextFrame};
    return returnedKeyFrames;
}

float Animator::calculateProgression(KeyFrame previousFrame, KeyFrame nextFrame) {
    float totalTime = nextFrame.getTimeStamp() - previousFrame.getTimeStamp();
    float currentTime = animationTime - previousFrame.getTimeStamp();
    return currentTime / totalTime;
}
std::map<std::string, glm::mat4> Animator::interpolatePoses(KeyFrame previousFrame, KeyFrame nextFrame, float progression) {
    std::map<std::string, glm::mat4> currentPose;
    for (std::pair<std::string, JointTransform> jointName : previousFrame.getJointKeyFrames()) {
        JointTransform previousTransform = previousFrame.getJointKeyFrames().at(jointName.first);
        JointTransform nextTransform = nextFrame.getJointKeyFrames().at(jointName.first);
        JointTransform currentTransform;
        currentTransform = currentTransform.interpolate(previousTransform, nextTransform, progression);
        currentPose.insert(std::pair<std::string,glm::mat4>(jointName.first, currentTransform.getLocalTransform()));
    }
    return currentPose;
}