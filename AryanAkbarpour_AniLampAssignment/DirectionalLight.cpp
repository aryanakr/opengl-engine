/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "DirectionalLight.h"

DirectionalLight::DirectionalLight(Shader& shader, Camera& camera, glm::vec3 pos, glm::vec2 angles, Material material, std::string name)
	:
	Light(shader, camera, pos, angles, material, name)
{}

DirectionalLight::~DirectionalLight()
{
}

void DirectionalLight::initialize()
{
	Mesh lightMesh = MeshLibrary::cylinderMesh(0.5f, 0.5f, 2.0f, 8);
	glm::mat4 mm = model.modelMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(propsScaleFactor));
	this->model.setModelMatrix(mm);
	this->model.addMesh(lightMesh);

	model.shader.use();
	model.shader.setVec3("color", this->material.specular);
}

void DirectionalLight::render()
{
	if (showLightProp)
		model.Draw();
}

void DirectionalLight::setObjShaderUniforms(Shader& objShader, int index)
{
	glm::vec3 front;

	front.x = sin(glm::radians(yaw));;
	front.y = -1.0f * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
	front.z = -1.0f * sin(glm::radians(pitch)) * cos(glm::radians(yaw));
	front = glm::normalize(front);
	objShader.use();
	objShader.setVec3("dirLight.direction", front);
	objShader.setVec3("dirLight.ambient", material.ambient);
	objShader.setVec3("dirLight.diffuse", material.diffuse);
	objShader.setVec3("dirLight.specular", material.specular);
}

Light_Type DirectionalLight::getLightType()
{
	return Light_Type::DIRECTIONAL;
}

void DirectionalLight::light_str()
{
	std::cout << "Directional Light pitch: (" << pitch << ") and yaw: (" << yaw << ")" << std::endl;
}

void DirectionalLight::drawLightControlPanel()
{
	ImGui::Text("Light Transforms");
	float* posFloat3[3] = { &position.x, &position.y, &position.z };
	ImGui::SliderFloat3("Position", *posFloat3, -10.0f, 10.0f, "%.2f");
	ImGui::SliderFloat("Pitch", &pitch, -180.0f, 180.0f, "%.1f");
	ImGui::SliderFloat("Yaw", &yaw, -180.0f, 180.0f, "%.1f");
	ImGui::Text("Light Colors");
	float* ambientFloat3[3] = { &material.ambient.x, &material.ambient.y, &material.ambient.z };
	float* diffuseFloat3[3] = { &material.diffuse.x, &material.diffuse.y, &material.diffuse.z };
	float* specularFloat3[3] = { &material.specular.x, &material.specular.y, &material.specular.z };
	ImGui::SliderFloat3("Ambient", *ambientFloat3, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat3("Diffuse", *diffuseFloat3, 0.0f, 1.0f, "%.3f");
	ImGui::SliderFloat3("Specular", *specularFloat3, 0.0f, 1.0f, "%.3f");
	ImGui::Checkbox("Show Light Prop", &showLightProp);
	ImGui::Checkbox("Disable", &disabled);

	glm::mat4 modelMatrix(1);
	modelMatrix = glm::translate(modelMatrix, position);
	modelMatrix = modelMatrix * glm::scale(glm::mat4(1), glm::vec3(propsScaleFactor));
	modelMatrix = modelMatrix * glm::rotate(glm::mat4(1), glm::radians(pitch), glm::vec3(1, 0, 0));
	modelMatrix = modelMatrix * glm::rotate(glm::mat4(1), glm::radians(yaw), glm::vec3(0, 0, 1));

	model.setModelMatrix(modelMatrix);
}
