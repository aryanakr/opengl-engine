/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "PointLight.h"

PointLight::PointLight(Shader& shader, Camera& camera, glm::vec3 pos, glm::vec2 angles, Material material, std::string name)
    :
    Light(shader, camera, pos, angles, material, name)
{

    this->constant = 1.0f;
    this->linear = 0.09f;
    this->quadratic = 0.032f;

}


PointLight::~PointLight()
{
}

void PointLight::setAttenuationTerms(float constant, float linear, float quadratic)
{
    this->constant = constant;
    this->linear = linear;
    this->quadratic = quadratic;
}

void PointLight::initialize() 
{

    Mesh lightMesh = MeshLibrary::sphereMesh();
    glm::mat4 mm = model.modelMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
    this->model.setModelMatrix(mm);
    this->model.addMesh(lightMesh);

    model.shader.use();
    model.shader.setVec3("color", this->material.specular);
}

void PointLight::render() 
{
    if(showLightProp)
        model.Draw();
}

void PointLight::setObjShaderUniforms(Shader& objShader, int index)
{
    objShader.use();
    objShader.setVec3("pointLights["+std::to_string(index)+"].position", position);
    objShader.setFloat("pointLights[" + std::to_string(index) + "].constant", constant);
    objShader.setFloat("pointLights[" + std::to_string(index) + "].linear", linear);
    objShader.setFloat("pointLights[" + std::to_string(index) + "].quadratic", quadratic);
    objShader.setVec3("pointLights[" + std::to_string(index) + "].ambient", this->material.ambient);
    objShader.setVec3("pointLights[" + std::to_string(index) + "].diffuse", this->material.diffuse);
    objShader.setVec3("pointLights[" + std::to_string(index) + "].specular", this->material.specular);
    //cout << specular.y << endl;
}

Light_Type PointLight::getLightType()
{
    return Light_Type::POINTLIGHT;
}

void PointLight::light_str()
{

    std::cout << "PointLight at: (" << position.x << ", " << position.y << ", " << position.z << " )" << std::endl;
}

void PointLight::drawLightControlPanel()
{
    ImGui::Text("Light Transforms");
    float* posFloat3[3] = { &position.x, &position.y, &position.z };
    ImGui::SliderFloat3("Position", *posFloat3, -10.0f, 10.0f, "%.2f");
    //float* orientationFloat3[3] = { &orientation.x, &orientation.y, &orientation.z };
    //ImGui::SliderFloat3("Orientation", *posFloat3, -10.0f, 10.0f, "%.01f");
    ImGui::Text("Light Colors");
    float* ambientFloat3[3] = { &this->material.ambient.x, &this->material.ambient.y, &this->material.ambient.z };
    float* diffuseFloat3[3] = { &this->material.diffuse.x, &this->material.diffuse.y, &this->material.diffuse.z };
    float* specularFloat3[3] = { &this->material.specular.x, &this->material.specular.y, &this->material.specular.z };
    ImGui::SliderFloat3("Ambient", *ambientFloat3, 0.0f, 1.0f, "%.3f");
    ImGui::SliderFloat3("Diffuse", *diffuseFloat3, 0.0f, 1.0f, "%.3f");
    ImGui::SliderFloat3("Specular", *specularFloat3, 0.0f, 1.0f, "%.3f");
    ImGui::Text("Attenuation Parameters");
    ImGui::SliderFloat("Constant", &constant, 0.0f, 1.0f, "%.3f");
    ImGui::SliderFloat("Linear", &linear, 0.0f, 1.0f, "%.3f");
    ImGui::SliderFloat("Quadratic", &quadratic, 0.0f, 1.0f, "%.3f");
    ImGui::Checkbox("Show Light Prop", &showLightProp);
    ImGui::Checkbox("Disable", &disabled);

    glm::mat4 modelMatrix(1);
    modelMatrix = glm::translate(modelMatrix, position);
    model.setModelMatrix(modelMatrix);

}
