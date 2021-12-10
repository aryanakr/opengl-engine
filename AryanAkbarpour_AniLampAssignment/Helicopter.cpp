/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "Helicopter.h"

/**
  * @desc Create helicopter object
  * @param Camera& camera - scene camera refrence
  *		   std::vector<Model>& models - main models vector refrence
  *		   vector<SGNode*> roots - main root nodes vector refrence
*/
void Helicopter::initialize(Camera& camera, std::vector<Model>& models, std::vector<SGNode*>& roots)
{
    // load body
	Shader helicopterShader("defaultShader.vs", "defaultShader.fs");
	Material helicopterMaterial(glm::vec3(1.0f, 1.0f, 0.31f), glm::vec3(1.0f, 0.5f, 0.5f), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
	std::string filepath = "$(ProjectDir)/../Assets/helicopter/HelicopterBody.obj";
	Model helicopterBodyModel(helicopterShader, camera, glm::mat4(1.0f), helicopterMaterial, filepath, true);
	models.push_back(helicopterBodyModel);

	filepath = "$(ProjectDir)/../Assets/helicopter/HelicopterPropeller.obj";
	Model helicopterPropellerModel(helicopterShader, camera, glm::mat4(1.0f), helicopterMaterial, filepath, true);
	models.push_back(helicopterPropellerModel);

	// Creating helicopter node hierarchy
	SGNode* heliRoot_Node = new NameNode("Helicopter");
	glm::mat4 m = glm::mat4(1);
	m = m * glm::translate(glm::mat4(1), heliPos);
	m = m * glm::scale(glm::mat4(1), glm::vec3(heliModelScaleFactor));
	m = m * glm::rotate(glm::mat4(1), glm::radians(heliOrientation), glm::vec3(0, 1, 0));
	SGNode* heliRootTransform_Node = new TransformNode("Root Transform", m);
	SGNode* heliPartsTransform_Node = new TransformNode("Parts Transform", glm::mat4(1));
	SGNode* heliParts_Node = new NameNode("Helicopter Parts");

	SGNode* heliBody_Node = new NameNode("Body");
	m = glm::mat4(1);
	SGNode* heliBodyTransform_Node = new TransformNode("Body Transform", m);
	SGNode* heliBodyModel_Node = new ModelNode("Body Model (Imported)", helicopterBodyModel);

	SGNode* heliPropeller_Node = new NameNode("Propeller");
	m = glm::mat4(1);
	m = m * glm::translate(glm::mat4(1), propellerOffset);
	SGNode* heliPropellerTransform_Node = new TransformNode("Propeller Transform", m);
	SGNode* heliPropellerModel_Node = new ModelNode("Propeller Model (Imported)", helicopterPropellerModel);

	heliPropellerTransform_Node->addChild(heliPropellerModel_Node);
	heliPropeller_Node->addChild(heliPropellerTransform_Node);
	heliBodyTransform_Node->addChild(heliBodyModel_Node);
	heliBody_Node->addChild(heliBodyTransform_Node);
	heliParts_Node->addChild(heliBody_Node);
	heliParts_Node->addChild(heliPropeller_Node);
	heliPartsTransform_Node->addChild(heliParts_Node);
	heliRootTransform_Node->addChild(heliPartsTransform_Node);
	heliRoot_Node->addChild(heliRootTransform_Node);
	heliRoot_Node->update();
	
	rootNode = heliRoot_Node;
	roots.push_back(heliRoot_Node);

}

/**
  * @desc Check if helicopter is above table
  * @return true if position above table
*/
bool Helicopter::isAboveTable()
{
	glm::mat4* rootTransform = nullptr;
	rootNode->getTransformByName("Root Transform", rootTransform);
	if (rootTransform == nullptr) {
		std::cout << "transform return error" << std::endl;
	}
	glm::vec3 scale;
	glm::quat rotation;
	glm::vec3 translation;
	glm::vec3 skew;
	glm::vec4 perspective;
	glm::decompose(*rootTransform, scale, rotation, translation, skew, perspective);
	if (abs(translation.x) < 3.5 && translation.z > 2.3f)
		return true;

	return false;
}

Helicopter::Helicopter()
{
	rootNode = nullptr;
}

Helicopter::~Helicopter()
{
}

/**
  * @desc draw imgui control panel window
*/
void Helicopter::drawControlWindow()
{
	if (ImGui::Begin("Helicopter Remote Control")) {
		ImGui::Text("Motor Control");
		if (ImGui::Button("ON/OFF"))
		{
			if (isAboveTable())
				groundHeight = 2.7f;
			else
				groundHeight = 0.1f;
			reachedCorrectHeight = false;
			if (engineRunning)
			{
				engineRunning = false;
			}
			else
			{
				engineRunning = true;
			}

		}
		ImGui::Text("Flight Control");
		float spacing = ImGui::GetStyle().ItemInnerSpacing.x;
		ImGui::PushButtonRepeat(true);
		if (ImGui::ArrowButton("##left", ImGuiDir_Left))
		{
			if (engineRunning) {
				rootNode->rotateTransformByName(1.0f, glm::vec3(0, 1, 0), "Root Transform");
			}

		}
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::Button("Forward"))
		{
			if (engineRunning) {
				rootNode->translateTransformByName(glm::vec3(0.35f, 0.0f, 0.0f), "Root Transform");
			}

		}
		ImGui::SameLine(0.0f, spacing);
		if (ImGui::ArrowButton("##right", ImGuiDir_Right))
		{
			if (engineRunning) {
				rootNode->rotateTransformByName(-1.0f, glm::vec3(0, 1, 0), "Root Transform");
			}
		}
		ImGui::PopButtonRepeat();
		ImGui::SameLine();

	}
	ImGui::End();
}

/**
  * @desc process helicopter animations

*/
void Helicopter::runAnimation(float current_time)
{
	// Rotating Propeller
	if (engineRunning && propellerRev < 20.0f)
		propellerRev += 0.15f;

	if (!engineRunning && propellerRev > 0.0f)
		propellerRev -= 0.15f;

	if (propellerRev > 0.0f)
	{
		rootNode->rotateTransformByName(propellerRev, glm::vec3(0, 1, 0), "Propeller Transform");

	}
	if (engineRunning && reachedCorrectHeight)
	{
		float heightDelta = sin(current_time - wobbleAnimStart) / 100;
		rootNode->translateTransformByName(glm::vec3(0, heightDelta, 0), "Root Transform");

	}

	if (!reachedCorrectHeight)
	{
		glm::mat4* rootTransform = nullptr;
		rootNode->getTransformByName("Root Transform", rootTransform);
		if (rootTransform == nullptr) {
			std::cout << "transform return error" << std::endl;
		}
		glm::vec3 scale;
		glm::quat rotation;
		glm::vec3 translation;
		glm::vec3 skew;
		glm::vec4 perspective;
		glm::decompose(*rootTransform, scale, rotation, translation, skew, perspective);

		if (engineRunning)
		{
			verticalSpeed += 0.0025f;
			if (translation.y >= flightHeight)
			{
				reachedCorrectHeight = true;
				verticalSpeed = 0.0f;
			}
			else
			{
				rootNode->translateTransformByName(glm::vec3(0, verticalSpeed, 0), "Root Transform");
			}
		}
		else
		{
			verticalSpeed = -0.1f;
			if (translation.y <= groundHeight)
			{
				rootNode->translateTransformByName(glm::vec3(0, groundHeight - translation.y, 0), "Root Transform");
				reachedCorrectHeight = true;
				verticalSpeed = 0.0f;
			}
			else
			{
				rootNode->translateTransformByName(glm::vec3(0, verticalSpeed, 0), "Root Transform");
			}
		}
	}

	rootNode->update();
}
