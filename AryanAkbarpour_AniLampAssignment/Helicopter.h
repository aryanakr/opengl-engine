/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#include "SGNode.h"
#include "Camera.h"
#include "Model.h"

#include "NameNode.h"
#include "TransformNode.h"
#include "ModelNode.h"

#include <vector>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "glm/gtx/string_cast.hpp"
#include "glm/gtx/matrix_decompose.hpp"


class Helicopter
{
public:
	
	Helicopter();
	~Helicopter();

	void drawControlWindow();
	void runAnimation(float current_time);
	bool isAboveTable();
	void initialize(Camera& camera, std::vector<Model>& models, std::vector<SGNode*>& roots);

private:
	SGNode* rootNode;

	// initial transforms
	float heliModelScaleFactor = 0.30f;
	glm::vec3 propellerOffset = glm::vec3(-0.270, 2.160, 0);
	glm::vec3 heliPos = glm::vec3(-2.5, 2.7, 4.5);
	float heliOrientation = 45.0f;

	// animation values
	bool engineRunning = false;
	float flightHeight = 4.7f;
	bool reachedCorrectHeight = true;
	float wobbleAnimStart = 0.0f;
	float propellerRev = 20.0f;
	float verticalSpeed = 0.0f;
	float groundHeight = 0.0f;

	
};

