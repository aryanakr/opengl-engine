/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#ifndef LIGHT_H
#define LIGHT_H
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/matrix_decompose.hpp>
#include "Shader.h"
#include "Model.h"
#include "MeshLibrary.h"
#include <optional>
enum class Light_Type {
	LIGHT,
	DIRECTIONAL,
	POINTLIGHT,
	SPOTLIGHT
};
class Light{
public:
	explicit Light(Shader& shader, Camera& camera, glm::vec3 pos, glm::vec2 angles, Material& material,std::string name);

	virtual void initialize();
	virtual void render();
	virtual void setObjShaderUniforms(Shader& objShader, int index);
	
	virtual void drawLightNodes(int& nodeIndexTracked, std::optional<int>& selectedIndex, Light*& pSelectedNode);
	virtual void drawLightControlPanel();
	virtual void drawModel();

	virtual Light_Type getLightType();
	virtual void light_str();

	void updateTransformsMatrix(glm::mat4 m);
	void setShowLightProp(bool state);
	bool getShowLightProp();

	bool isDisabled();

protected:
	bool disabled = false;
	float pitch;
	float yaw;

	glm::vec3 position;

	Model model;
	Material material;

	std::string name;

	bool showLightProp = true;
	float propsScaleFactor = 0.5f;

};

#endif