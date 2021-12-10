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

#include "Shader.h"
#include "stb_image.h"
#include <vector>
#include "Camera.h"

class SkyBox
{
public:
	SkyBox(Camera& camera);
	~SkyBox();

	void initialize();
	void draw();
	unsigned int loadTexture(char const* path);
	unsigned int loadCubemap(std::vector<std::string> faces);

private:
	Camera* camera;
	Shader skyboxShader;

	unsigned int skyboxVAO, skyboxVBO = 0;
	unsigned int cubeVAO, cubeVBO = 0;
	unsigned int cubemapTexture = 0;
};