/**
  * This file is part of COM3503 assignment
  * 
  * I declare that this code is my own work 
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk 
*/
#pragma once

#include "Camera.h"
#include "Model.h"
#include "MeshLibrary.h"
#include "LightSystem.h"
#include "PointLight.h"

class Room
{
public:
	Room();
	~Room();

	void initialize(Camera& camera, std::vector<Model>& models);

private:
	float floorWidth = 13.0f;
	float floorLength = 13.0f;
	float wallHeight = 8.0f;

};