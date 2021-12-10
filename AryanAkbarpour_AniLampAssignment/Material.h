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

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Shader.h"

class Material
{
public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float shininess;

    Material(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular, float shininess)
    {
        this->ambient = ambient;
        this->diffuse = diffuse;
        this->specular = specular;
        this->shininess = shininess;
    }

    void setShaderUniforms(Shader& shader)
    {
        shader.use();
        shader.setVec3("material.ambient", this->ambient);
        shader.setVec3("material.diffuse", this->diffuse);
        shader.setVec3("material.specular", this->specular);
        shader.setFloat("material.shininess", this->shininess);
    }
    
    void drawImGuiControlPanel()
    {
        ImGui::Text("Material Properties");

        float* ambientFloat3[3] = { &ambient.x, &ambient.y, &ambient.z };
        ImGui::SliderFloat3("Ambient", *ambientFloat3, 0.0f, 1.0f, "%.3f");

        float* diffuseFloat3[3] = { &diffuse.x, &diffuse.y, &diffuse.z };
        ImGui::SliderFloat3("Diffuse", *diffuseFloat3, 0.0f, 1.0f, "%.3f");

        float* specularFloat3[3] = { &specular.x, &specular.y, &specular.z };
        ImGui::SliderFloat3("Specular", *specularFloat3, 0.0f, 1.0f, "%.3f");

        ImGui::SliderFloat("Yaw", &shininess, 0.0f, 1000.0f, "%.1f");
    }
};