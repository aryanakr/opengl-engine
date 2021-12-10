/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#ifndef LIGHTSYSTEM_H
#define LIGHTSYSTEM_H

#include "Shader.h"
#include "Camera.h"

#include "Material.h"
#include "Light.h"

#include <vector>
#include <iostream>
#include <stack>
#include <unordered_map>


class LightSystem
{
public:
	LightSystem();
	~LightSystem();

	void addlight(Light* light);
	void initialize();
	void render();

	int lightsNum();
	void lightSystem_Str();

	void setObjShader(Shader& shader);
	std::vector<Light*> lights;

	void showLightSystemControlWindow(int& nodeIndexTracked, std::optional<int>& selectedIndex, Light*& pSelectedNode);
private:


};

#endif