/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#include "SGNode.h"
#include "Model.h"
#include "Shader.h"
class ModelNode : public SGNode
{
public:
	ModelNode(std::string name, Model& m);
	
	void draw() override;
	void update(glm::mat4 t) override;
	void drawNodeControlPanel() override;
	
	Model& getModel();

protected:
	Model model;
};