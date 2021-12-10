/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "TransformNode.h"

TransformNode::TransformNode(std::string name, glm::mat4 t)
	:
	SGNode(name)
{
	transform = glm::mat4(t);
}

void TransformNode::setTransformByName(std::string name, glm::mat4 m)
{
    if (this->name == name) {
        transform = glm::mat4(m);
    }
    else {
        for (auto&& c : children) {
            c->setTransformByName(name, m);
        }
    }
}

void TransformNode::update(glm::mat4 t)
{
    worldTransform = t;
    t = worldTransform * transform;
    for (auto&& c : children) {
        c->update(t);
    }
}

void TransformNode::translateTransformByName(glm::vec3 t, std::string name)
{
    if (this->name == name) {
        this->transform = glm::translate(transform, t);
        return;
    }
    for (auto&& c : children) {
        c->translateTransformByName(t, name);
    }
    

}

glm::mat4 TransformNode::getTranform()
{
    return this->transform;
}

void TransformNode::setTranformModel(glm::mat4 model)
{
    this->transform = model;
}

std::string TransformNode::getNodeType_str()
{
    return "TransformNode";
}

void TransformNode::drawNodeControlPanel()
{
    if (!drawInitialized) {
        glm::vec3 scale;
        glm::quat rotation;
        glm::vec3 translation;
        glm::vec3 skew;
        glm::vec4 perspective;
        glm::decompose(transform, scale, rotation, translation, skew, perspective);
        glm::vec3 euler = glm::eulerAngles(rotation);
        euler = glm::vec3(glm::degrees(euler.x), glm::degrees(euler.y), glm::degrees(euler.z));

        draw_translation = translation;
        draw_orientation = euler;
        draw_scale = scale;

        drawInitialized = true;
    }
    
    ImGui::Text("Orientation");

    ImGui::SliderFloat("Roll", &draw_orientation.x, -180.0f, 180.0f);
    ImGui::SliderFloat("Pitch", &draw_orientation.y, -180.0f, 180.0f);
    ImGui::SliderFloat("Yaw", &draw_orientation.z, -180.0f, 180.0f);
    ImGui::Text("Position");
    ImGui::SliderFloat("pos X", &draw_translation.x, -20.0f, 20.0f, "%.2f");
    ImGui::SliderFloat("pos Y", &draw_translation.y, -20.0f, 20.0f, "%.2f");
    ImGui::SliderFloat("pos Z", &draw_translation.z, -20.0f, 20.0f, "%.2f");
    ImGui::Text("Scale");
    ImGui::SliderFloat("scale X", &draw_scale.x, 0.0f, 5.0f, "%.2f");
    ImGui::SliderFloat("scale Y", &draw_scale.y, 0.0f, 5.0f, "%.2f");
    ImGui::SliderFloat("scale Z", &draw_scale.z, 0.0f, 5.0f, "%.2f");

    if (ImGui::Button("Apply"))
    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, glm::vec3(draw_translation.x, draw_translation.y, draw_translation.z));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(draw_orientation.x), glm::vec3(1, 0, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(draw_orientation.y), glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, glm::radians(draw_orientation.z), glm::vec3(0, 0, 1));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(draw_scale.x, draw_scale.y, draw_scale.z));

        this->setTranformModel(modelMatrix);
        this->update(worldTransform);
    }

}


void TransformNode::rotateTransformByName(float degrees, glm::vec3 axis, std::string name)
{
    if (this->name == name) {
        this->transform = glm::rotate(this->transform, glm::radians(degrees), axis);
        return;
    }
    for (auto&& c : children)
    {
        c->rotateTransformByName(degrees, axis, name);
    }
}

void TransformNode::getTransformByName(std::string name, glm::mat4*& res)
{
    if (res != nullptr)
        return;
    if (this->name == name) {
        res = &this->transform;
        return;
    }
    for (auto&& c : children)
    {
        c->getTransformByName(name, res);
    }
}




