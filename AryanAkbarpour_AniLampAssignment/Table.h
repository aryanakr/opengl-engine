/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
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
#include "MeshLibrary.h"
#include "NameNode.h"
#include "TransformNode.h"
#include "ModelNode.h"

#include <vector>

class Table
{
public:
	Table();
	~Table();

	void initialize(Camera& camera, std::vector<Model>& models, std::vector<SGNode*>& roots);

private:

	SGNode* rootNode;

	float tableWidth = 7.0f;
	float tableDepth = 4.0f;
	float tableThickness = 0.2f;
	float tableLegWidth = 0.4f;
	float tableLegHeight = 2.5f;
	float floorLength = 13.0f;
};