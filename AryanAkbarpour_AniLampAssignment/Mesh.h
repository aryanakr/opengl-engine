/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * This file contains codes from online tutorial
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#ifndef MESH_H
#define MESH_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <string>
#include "TextureLibrary.h"
#include "Shader.h"

using namespace std;

struct Vertex {
	glm::vec3 position;
	glm::vec3 normal;
	glm::vec2 texCoords;
	glm::vec3 tangent;
	glm::vec3 bitangent;
};

struct Texture{
	unsigned int id;
	std::string type;
	std::string path;
};

class Mesh {
public:
	std::vector<Vertex> vertices;
	std::vector<unsigned int> indices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures);
	void addTextures(std::string diffuse_filename, std::string specular_filename);
	void Draw(Shader& shader);
private:
	unsigned int VAO, VBO, EBO;
	void setupMesh();
};

#endif
