/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "SpotLight.h"
#include "glm/gtx/string_cast.hpp"

SpotLight::SpotLight(Shader& shader, Camera& camera, glm::vec3 pos, glm::vec2 angles, Material material, std::string name, float cutOff, float outerCutOff)
    :
    Light(shader, camera, pos, angles, material, name)
{
    this->cutOff = cutOff;
    this->outerCutOff = outerCutOff;

    this->constant = 1.0f;
    this->linear = 0.09f;
    this->quadratic = 0.032f;
}

SpotLight::~SpotLight()
{
}

void SpotLight::setAttenuationTerms(float constant, float linear, float quadratic)
{
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}


void SpotLight::initialize()
{
    Mesh lightMesh = MeshLibrary::cylinderMesh(0.5f, 0.1f, 1.0f, 16);
    glm::mat4 mm = model.modelMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(propsScaleFactor));
    this->model.setModelMatrix(mm);
    this->model.addMesh(lightMesh);

    model.shader.use();
    model.shader.setVec3("color", this->material.specular);
}

void SpotLight::render()
{
    if(showLightProp)
        model.Draw();
}

void SpotLight::setObjShaderUniforms(Shader& objShader, int index)
{
    // want the light to initialize facing down
    glm::vec3 front;

    front.x = sin(glm::radians(yaw));;
    front.y = -1.0f * cos(glm::radians(pitch)) * cos(glm::radians(yaw));
    front.z = -1.0f * sin(glm::radians(pitch)) * cos(glm::radians(yaw));
    front = glm::normalize(front);
    objShader.use();
    objShader.setVec3("spotLights[" + std::to_string(index) + "].position", position);
    objShader.setVec3("spotLights[" + std::to_string(index) + "].direction", front);
    objShader.setFloat("spotLights[" + std::to_string(index) + "].cutOff", cutOff);
    objShader.setFloat("spotLights[" + std::to_string(index) + "].outerCutOff", outerCutOff);
    objShader.setVec3("spotLights[" + std::to_string(index) + "].ambient", this->material.ambient);
    objShader.setVec3("spotLights[" + std::to_string(index) + "].diffuse", this->material.diffuse);
    objShader.setVec3("spotLights[" + std::to_string(index) + "].specular", this->material.specular);
    objShader.setFloat("spotLights[" + std::to_string(index) + "].constant", constant);
    objShader.setFloat("spotLights[" + std::to_string(index) + "].linear", linear);
    objShader.setFloat("spotLights[" + std::to_string(index) + "].quadratic", quadratic);
}

Light_Type SpotLight::getLightType()
{
    return Light_Type::SPOTLIGHT;
}

void SpotLight::light_str()
{
    std::cout << "SpotLight at position: (" << position.x << ", " << position.y
        << ", " << position.z << " )" << " with pitch angle: (" << pitch
        << ") and Yaw angle ( " << yaw << ")"<< std::endl;
}

void SpotLight::drawLightControlPanel()
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
    ImGui::Text("Attenuation Parameters");
    ImGui::SliderFloat("Constant", &constant, 0.0f, 1.0f, "%.3f");
    ImGui::SliderFloat("Linear", &linear, 0.0f, 1.0f, "%.3f");
    ImGui::SliderFloat("Quadratic", &quadratic, 0.0f, 1.0f, "%.3f");
    ImGui::SliderFloat("Cut Off", &cutOff, 0.0f, 1.0f, "%.3f");
    ImGui::Text("Cut Off Parameters");
    ImGui::SliderFloat("Outer Cut Off", &outerCutOff, 0.0f, 1.0f, "%.3f");
    ImGui::Checkbox("Show Light Prop", &showLightProp);
    ImGui::Checkbox("Disable", &disabled);

    glm::mat4 modelMatrix(1);
    modelMatrix = glm::translate(modelMatrix, position); 
    modelMatrix = modelMatrix * glm::scale(glm::mat4(1), glm::vec3(propsScaleFactor));
    modelMatrix = modelMatrix * glm::rotate(glm::mat4(1), glm::radians(pitch), glm::vec3(1, 0, 0));
    modelMatrix = modelMatrix * glm::rotate(glm::mat4(1), glm::radians(yaw), glm::vec3(0, 0, 1));
    
    model.setModelMatrix(modelMatrix);
}
