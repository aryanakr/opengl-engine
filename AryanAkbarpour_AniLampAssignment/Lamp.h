/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once

#include "Camera.h"
#include "SGNode.h"
#include "NameNode.h"
#include "TransformNode.h"
#include "ModelNode.h"
#include "Model.h"
#include "LightNode.h"
#include "SpotLight.h"
#include "LightSystem.h"

#include <time.h>

class Lamp
{
public:
    Lamp();

    void initialize(Camera& camera, vector<Model>& models, vector<SGNode*>& roots, LightSystem& lightSystem);
    void drawControlWindow();
    void runAnimation();
    void creatNewTarget();
    void setResetTarget();
    void printTarget();
    void printCurrent();
    void updateJointsTransforms();

private:
    SGNode* MainRoot;

    bool isAnimationRunning = false;
    bool isAnglesSet = false;

    float initialLowerJointAngX = 30.0f;
    float initialMiddleJointAngX = -70.0f;
    float initialupperJointAngX = 10.0f;
    float initiallowerJointAngY = 0.0f;

    float lowerJointAngX = 30.0f;
    float middleJointAngX = -70.0f;
    float upperJointAngX = 10.0f;
    float lowerJointAngY = 0.0f;

    // joint rotation limits
    float lowerJointXMin = 10.0f;
    float lowerJointXMax = 70.0f;

    float lowerJointYMin = -45.0f;
    float lowerJointYMax = 45.0f;

    float middleJointXMin = -100.0f;
    float middleJointXMax = -30.0f;

    float upperJointXMin = -40.0f;
    float upperJointXMax = 15.0f;

    // Target Orientations
    float lowerJointXTarget = 0.0f;
    float lowerJointYTarget = 0.0f;
    float middleJointXTarget = 0.0f;
    float upperJointXTarget = 0.0f;

    glm::vec3 rootPos = glm::vec3(2.42f, 2.7f , 4.55f);
    glm::vec3 rootScale = glm::vec3(0.50f);
    glm::vec3 baseScale = glm::vec3(1.65f, 0.40f, 2.00f);
    glm::vec3 lowerJointModelScale = glm::vec3(0.6);
    glm::vec3 lowerJointPos = glm::vec3(0.0f, baseScale.y, 0.35f);
    glm::vec3 lowerArmPos = glm::vec3(0);
    glm::vec3 lowerArmScale = glm::vec3(0.45f, 1.80f, 0.45f);

    glm::vec3 middleJointPos = glm::vec3(0, lowerArmScale.y, 0);
    glm::vec3 middleJointModelScale = glm::vec3(0.50, 0.50f, 0.50f);
    glm::vec3 middleJointModelPos = glm::vec3((float)middleJointModelScale.y / 2.0f - 0.02, 0.0f, 0.0f);

    glm::vec3 upperJointPos = glm::vec3(0, lowerArmScale.y, 0);

    glm::vec3 headPos = glm::vec3(0.0f, -0.15f, -0.15f);
    glm::vec3 headScale = glm::vec3(0.35f);

    glm::vec3 hatPos = glm::vec3(0.0f, 0.85f, -0.01f);
    glm::vec3 hatScale = glm::vec3(0.20f);

    glm::vec3 tailScale = glm::vec3(0.30f);

    glm::vec3 lowerJointAng = glm::vec3(45.0f);
    glm::vec3 bulbPos = glm::vec3(0.0f, 0.48f, -1.25f);

    std::vector<float> randoms;
    int randomOffset = 50;

    // control slider values
    float sliderLowerX = lowerJointAngX;
    float sliderlowerY = lowerJointAngY;
    float slidermiddleX = middleJointAngX;
    float sliderupperX = upperJointAngX;
};
