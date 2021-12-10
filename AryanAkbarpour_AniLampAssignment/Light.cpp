/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "Light.h"

Light::Light(Shader& shader, Camera& camera, glm::vec3 pos, glm::vec2 angles, Material& material, std::string name)
	:
	model(shader, camera, glm::mat4(1), material, false),
	position(pos),
	pitch(angles.x),
	yaw(angles.y),
	material(material)
{
	this->name = name;
	glm::mat4 modelMatrix(1);
	modelMatrix = glm::translate(modelMatrix, pos);
	modelMatrix = modelMatrix * glm::rotate(glm::mat4(1), glm::radians(yaw), glm::vec3(0, 0, 1));
	modelMatrix = modelMatrix * glm::rotate(glm::mat4(1), glm::radians(pitch), glm::vec3(1, 0, 0));
	this->model.setModelMatrix(modelMatrix);
}

void Light::initialize()
{}
void Light::render()
{
	if (showLightProp)
		model.Draw();
}
void Light::setObjShaderUniforms(Shader& objShader, int index)
{
}
Light_Type Light::getLightType()
{
	return Light_Type::LIGHT;
}
void Light::light_str()
{
	std::cout << "Vanilla Light" << std::endl;
}

void Light::updateTransformsMatrix(glm::mat4 m)
{
	m = m * glm::scale(glm::mat4(1), glm::vec3(propsScaleFactor));
	this->model.setModelMatrix(m);

	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(m, scale, rotation, translation, skew, perspective);
	glm::vec3 euler = glm::eulerAngles(rotation);
	euler = glm::vec3(glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z));


	this->position = translation;
	this->pitch = -euler.x;
	this->yaw = -euler.z;
}

void Light::setShowLightProp(bool state)
{
	showLightProp = state;
}

bool Light::getShowLightProp()
{
	return showLightProp;
}

bool Light::isDisabled()
{
	return this->disabled;
}

void Light::drawLightNodes(int& nodeIndexTracked, std::optional<int>& selectedIndex, Light*& pSelectedNode)
{
	const int currentNodeIndex = nodeIndexTracked;
	nodeIndexTracked++;
	const auto node_flags = ImGuiTreeNodeFlags_OpenOnArrow
		| ((currentNodeIndex == selectedIndex.value_or(-1)) ? ImGuiTreeNodeFlags_Selected : 0)
		| ImGuiTreeNodeFlags_Leaf;

	std::string nodeName = this->name;
	switch (this->getLightType()) {
	case Light_Type::DIRECTIONAL:
		nodeName += " (Directional)";
		break;
	case Light_Type::POINTLIGHT:
		nodeName += " (PointLight)";
		break;
	case Light_Type::SPOTLIGHT:
		nodeName += " (SpotLight)";
		break;
	case Light_Type::LIGHT:
		nodeName += " (Light)";
		break;
	}

	if (ImGui::TreeNodeEx((void*)(intptr_t)currentNodeIndex, node_flags, nodeName.c_str()))
	{
		if (ImGui::IsItemClicked())
		{
			selectedIndex = currentNodeIndex;
			pSelectedNode = const_cast<Light*>(this);
		}
		ImGui::TreePop();
	}
}

void Light::drawLightControlPanel()
{
}

void Light::drawModel()
{
	this->model.Draw();
}

