/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#include "SGNode.h"
#include "Light.h"
#include "Shader.h"
class LightNode : public SGNode
{
public:
	LightNode(std::string name, Light*& l);

	void draw() override;
	void update(glm::mat4 t) override;

	void drawNodeControlPanel() override;

private:
	Light* light;

};