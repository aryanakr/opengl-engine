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

#include "Shader.h"
#include "Camera.h"

#include "Light.h"


class DirectionalLight : public Light
{
public:

	DirectionalLight(Shader& shader, Camera& camera, glm::vec3 pos, glm::vec2 angles, Material material, std::string name);
	~DirectionalLight();

	void initialize() override;
	void render() override;
	void setObjShaderUniforms(Shader& objShader, int index) override;
	Light_Type getLightType() override;
	void light_str() override;
	void drawLightControlPanel() override;

	int index = 0;

};
