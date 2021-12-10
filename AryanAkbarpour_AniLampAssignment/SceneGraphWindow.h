/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"
#include "SGNode.h"
#include <optional>
#include <map>
#include <string>
#include <stack>
#include <unordered_map>
class SceneGraphWindow
{
    friend SGNode;
public:
    SceneGraphWindow() {};
	void show(std::vector<SGNode*>& roots, int& nodeIndexTracked, std::optional<int>& selectedIndex,SGNode*& pSelectedNode) {
        if (ImGui::Begin("Scene Graph")) {
            ImGui::Columns(2, nullptr, true);

            for (auto& r : roots) {
                r->drawImGuiSceneGraph(nodeIndexTracked, selectedIndex, pSelectedNode, r->getName(),true);
            }

            ImGui::NextColumn();
            if (selectedIndex.has_value())
            {
                pSelectedNode->drawNodeControlPanel();

            }
        }
        ImGui::End();
	}

};