/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "SGNode.h"

SGNode::SGNode(std::string name)
{
	this->name = name;
	worldTransform = glm::mat4(1);
}

void SGNode::addChild(SGNode* &child)
{
	children.push_back(child);
}

void SGNode::update()
{
	update(worldTransform);
}

void SGNode::update(glm::mat4 t)
{
	worldTransform = t;
	for (auto&& c : children) {
		c->update(t);
	}

}

void SGNode::draw()
{

	for (auto&& c : children) {
		c->draw();
	}
}

void SGNode::setTransformByName(std::string name, glm::mat4 m)
{
	if (this->name == name) {
		return;
	}
	for (auto&& c : children) {
		c->setTransformByName(name, m);
	}
}

std::string SGNode::getName()
{
	return this->name;
}

glm::mat4 SGNode::getTranform()
{
	return glm::mat4(1);
}

std::string SGNode::getNodeType_str()
{
	return "SGNode";
}

void SGNode::setTranformModel(glm::mat4 model)
{
	return;
}

void SGNode::rotateTransformByName(float degrees, glm::vec3 axis, std::string name)
{
	if (this->name == name) {
		return;
	}
	for (auto&& c : children)
	{
		c->rotateTransformByName(degrees, axis, name);
	}
}

void SGNode::drawImGuiSceneGraph(int& nodeIndexTracked, std::optional<int>& selectedIndex, SGNode*& pSelectedNode, std::string rootId, bool isRoot)
{
	const int currentNodeIndex = nodeIndexTracked;
	nodeIndexTracked++;
	const auto node_flags = ImGuiTreeNodeFlags_OpenOnArrow
		| ((currentNodeIndex == selectedIndex.value_or(-1)) ? ImGuiTreeNodeFlags_Selected : 0)
		| ((children.size() == 0) ? ImGuiTreeNodeFlags_Leaf : 0);

	std::string nodeName = "";
	if (isRoot)
		nodeName = name;
	else
		nodeName = name + " ("+rootId+")";
	if (ImGui::TreeNodeEx((void*)(intptr_t)currentNodeIndex, node_flags, nodeName.c_str()))
	{
		if (ImGui::IsItemClicked())
		{
			selectedIndex = currentNodeIndex;
			pSelectedNode = const_cast<SGNode*>(this);
		}
		for (auto&& c : children)
		{
			c->drawImGuiSceneGraph(nodeIndexTracked, selectedIndex, pSelectedNode, rootId,false);
		}
		ImGui::TreePop();
	}
	
}

void SGNode::getTransformByName(std::string name, glm::mat4*& res)
{
	if (this->name == name) {
		return;
	}

	for (auto&& c : children) {
		c->getTransformByName(name, res);
	}

}

void SGNode::translateTransformByName(glm::vec3 t, std::string name)
{
	if (this->name == name) {
		return;
	}
	for (auto&& c : children) {
		c->translateTransformByName(t, name);
	}
}

void SGNode::drawNodeControlPanel()
{
	std::string nameText = "SGNode Name: " + name;
	ImGui::Text(nameText.c_str());
}

