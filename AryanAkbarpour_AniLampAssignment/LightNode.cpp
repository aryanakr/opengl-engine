/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "LightNode.h"

LightNode::LightNode(std::string name, Light*& l)
	:
	SGNode(name),
	light(l)
{
}

void LightNode::draw()
{
	for (auto&& c : children) {
		c->draw();
	}
}

void LightNode::update(glm::mat4 t)
{
	worldTransform = t;
	light->updateTransformsMatrix(worldTransform);
	for (auto&& c : children) {
		c->update(t);
	}
}

void LightNode::drawNodeControlPanel()
{
	light->drawLightControlPanel();
}
