/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "LightSystem.h"

LightSystem::LightSystem()
{
}

LightSystem::~LightSystem()
{
}

void LightSystem::addlight(Light* light)
{
	lights.push_back(light);
}

void LightSystem::initialize()
{
	for (auto&& l : lights) {
		l->initialize();
	}
}

void LightSystem::render()
{
	for (auto&& l : lights) {
		if(!l->isDisabled())
			l->render();
	}
}

int LightSystem::lightsNum()
{
	int size = this->lights.size();
	cout << size << endl;
	return size;
}

void LightSystem::lightSystem_Str()
{
	int counter = 0;
	for (auto&& l : lights) {
		cout << "light " << counter << ": " << endl;
		l->light_str();
		counter++;
	}
	if (counter == 0) {
		cout << "no lights on scene" << endl;
	}
}

void LightSystem::setObjShader(Shader& shader)
{
	shader.use();
	int spotcounter = 0;
	int directionalCounter = 0;
	int pointCounter = 0;
	for (auto&& l : lights) {
		if (l->isDisabled())
			continue;
		if (l->getLightType() == Light_Type::POINTLIGHT) {
			l->setObjShaderUniforms(shader, pointCounter);
			pointCounter++;
		}
		else if (l->getLightType() == Light_Type::DIRECTIONAL) {
			l->setObjShaderUniforms(shader, directionalCounter);
			directionalCounter++;
		}
		else if (l->getLightType() == Light_Type::SPOTLIGHT) {
			l->setObjShaderUniforms(shader, spotcounter);
			spotcounter++;
		}
	}
	shader.setInt("numSpotLights", spotcounter);
	shader.setInt("numPointLights", pointCounter);

}

void LightSystem::showLightSystemControlWindow(int& nodeIndexTracked, std::optional<int>& selectedIndex, Light*& pSelectedNode)
{

    if (ImGui::Begin("LightSystem Control Window")) {
        ImGui::Columns(2, nullptr, true);

        for (auto& l : lights) {
            l->drawLightNodes(nodeIndexTracked, selectedIndex, pSelectedNode);
        }

        ImGui::NextColumn();
        if (selectedIndex.has_value())
        {
            pSelectedNode->drawLightControlPanel();
        }
    }
    ImGui::End();
}
