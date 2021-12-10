/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>

#include "Shader.h"
#include "Light.h"
#include "Model.h"

class SpotLight : public Light
{
public:
	float constant;
	float linear;
	float quadratic;

	float cutOff;
	float outerCutOff;

	SpotLight(Shader& shader, Camera& camera, glm::vec3 pos, glm::vec2 angles, Material material, std::string name, float cutOff, float outerCutOff);
	~SpotLight();

	void setAttenuationTerms(float constant, float linear, float quadratic);

	void initialize() override;
	void render() override;
	void setObjShaderUniforms(Shader& objShader, int index) override;
	Light_Type getLightType() override;
	void light_str() override;
	void drawLightControlPanel() override;

	int index = 0;

};
