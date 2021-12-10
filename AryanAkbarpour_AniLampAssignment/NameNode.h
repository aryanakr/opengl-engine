/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#include "SGNode.h"
class NameNode : public SGNode
{
public:
	NameNode(std::string name) : SGNode(name) {};
	void drawNodeControlPanel() override;

};