/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "NameNode.h"

void NameNode::drawNodeControlPanel()
{
	std::string nameText = "Name Node Name: " + name;
	ImGui::Text(nameText.c_str());
}
