/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "ModelNode.h"

ModelNode::ModelNode(std::string name, Model& m)
	:
	SGNode(name),
	model(m)
{
}

void ModelNode::draw()
{

	model.Draw();
	for (auto&& c : children) {
		c->draw();
	}
}

void ModelNode::update(glm::mat4 t)
{
	worldTransform = t;
	model.setModelMatrix(worldTransform);
	for (auto&& c : children) {
		c->update(t);
	}
}

void ModelNode::drawNodeControlPanel()
{
	std::string nameText = "ModelNode Name: " + name;
	ImGui::Text(nameText.c_str());
	model.getMaterial().drawImGuiControlPanel();
}

Model& ModelNode::getModel()
{
	return model;
}

