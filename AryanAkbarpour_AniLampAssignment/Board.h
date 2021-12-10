/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once

#include "Camera.h"
#include "Model.h"
#include "SGNode.h"
#include "MeshLibrary.h"
#include "NameNode.h"
#include "TransformNode.h"
#include "ModelNode.h"

class Board
{
public:

	Board();
	~Board();

	void initialize(Camera& camera, std::vector<Model>& models, std::vector<SGNode*>& roots);

private:
	SGNode* root;

	// inital transform values
	glm::vec3 rootPos = glm::vec3(0.0f, 5.23f, 6.49f);
	glm::vec3 boardScale = glm::vec3(5.5f, 0.25f, 4.0f);

	float frameDepth = 0.20f;
	float frameWidth = 0.25f;
	
	glm::vec3 pic1Pos = glm::vec3(1.20f, boardScale.y / 2 + 0.01f, -0.80f);
	glm::vec3 pic2Pos = glm::vec3(1.90f, boardScale.y / 2 + 0.01f, 0.90f);
	glm::vec3 pic3Pos = glm::vec3(-1.20f, boardScale.y / 2 + 0.01f, 0.60f);

	glm::vec3 pic1Scale = glm::vec3(2.30f, 1, 1.5f);
	glm::vec3 pic2Scale = glm::vec3(0.75f, 1, 0.75f);
	glm::vec3 pic3Scale = glm::vec3(2.00f, 1, 1.25f);
};