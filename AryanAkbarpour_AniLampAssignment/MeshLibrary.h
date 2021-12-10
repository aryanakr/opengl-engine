/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#ifndef MESHLIBRARY_H
#define MESHLIBRARY_H
#include "Mesh.h"
#include "TextureLibrary.h"

class MeshLibrary
{
public:
    static Mesh cylinderMesh(float bottomRadius, float topRadius, float height, int sectorCount);
    static Mesh cubeMesh();
    static Mesh planeMesh();
    static Mesh sphereMesh();
    static std::vector<float> getUnitCircleVertices(int sectorCount);



};
#endif


