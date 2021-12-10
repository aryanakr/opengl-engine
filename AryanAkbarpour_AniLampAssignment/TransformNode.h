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
#include <glm/gtx/matrix_decompose.hpp>

class TransformNode : public SGNode
{
public:
	TransformNode(std::string name, glm::mat4 t);

	void update(glm::mat4 t) override;

	void rotateTransformByName(float degrees, glm::vec3 axis, std::string name) override;
	void translateTransformByName(glm::vec3 t, std::string name) override;

	glm::mat4 getTranform() override;
	void getTransformByName(std::string name, glm::mat4*& res) override;


	void setTranformModel(glm::mat4 model) override;
	void setTransformByName(std::string name, glm::mat4 m) override;
	
	std::string getNodeType_str() override;
	void drawNodeControlPanel() override;

private:
	glm::mat4 transform;

	bool drawInitialized = false;
	glm::vec3 draw_translation;
	glm::vec3 draw_scale;
	glm::vec3 draw_orientation;
	
};