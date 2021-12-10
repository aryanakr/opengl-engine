#pragma once
#ifndef POINTLIGHT_H
#define POINTLIGHT_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Light.h"
#include "Model.h"

class PointLight : public Light
{
public:

	float constant;
	float linear;
	float quadratic;

	PointLight(Shader& shader, Camera& camera, glm::vec3 pos, glm::vec2 angles, Material material, std::string name);
	~PointLight();

	void setAttenuationTerms(float constant, float linear, float quadratic);

	void initialize() override;
	void render() override;
	void setObjShaderUniforms(Shader& objShader, int index) override;
	Light_Type getLightType() override;
	void light_str() override;
	void drawLightControlPanel() override;

	int index = 0;	

};

#endif
