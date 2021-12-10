/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include "Shader.h"

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include <optional>

class SGNode {
public:
	explicit SGNode(std::string name);

	void addChild(SGNode* &child);
	
	virtual void update();
	virtual void update(glm::mat4 t);
	virtual void draw();

	std::string getName();
	virtual glm::mat4 getTranform();
	virtual std::string getNodeType_str();
	virtual void setTranformModel(glm::mat4 model);

	virtual void getTransformByName(std::string name, glm::mat4*& res);
	virtual void setTransformByName(std::string name, glm::mat4 m);
	
	virtual void translateTransformByName(glm::vec3 t, std::string name);
	virtual void rotateTransformByName(float degrees, glm::vec3 axis, std::string name);

	void drawImGuiSceneGraph(int& nodeIndexTracked, std::optional<int>& selectedIndex, SGNode*& pSelectedNode, std::string rootId, bool isRoot);
	virtual void drawNodeControlPanel();

protected:


	std::string name;
	glm::mat4 worldTransform;
	std::vector<SGNode*> children;

};