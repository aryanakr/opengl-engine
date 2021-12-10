/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "Room.h"

Room::Room()
{}

Room::~Room()
{}

/**
  * @desc Create models of the room
  * @param Camera& camera - scene camera refrence
  *        std::vector<Model>& models - main models vector refrences
*/
void Room::initialize(Camera& camera, std::vector<Model>& models)
{
    // create static models
    // -------------------------
    // Floor Model
    Mesh floorMesh = MeshLibrary::planeMesh();
    floorMesh.addTextures("FloorTiles.png", "FloorTiles_Specular.png");
    Shader floorShader("defaultShader.vs", "defaultShader.fs");
    glm::mat4 floorModelMatrix = glm::mat4(1.0f);
    floorModelMatrix = glm::scale(floorModelMatrix, glm::vec3(floorWidth, 0.1f, floorLength));
    Material floorMaterial(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), 32.0f);
    Model floorModel = Model(floorShader, camera, floorModelMatrix, floorMaterial, false);
    floorModel.addMesh(floorMesh);
    models.push_back(floorModel);

    // Shrine Wall Model
    Shader shrineShader("defaultShader.vs", "defaultShader.fs");
    Material shrineMaterial(glm::vec3(1.0f), glm::vec3(3.0f), glm::vec3(1.0f), 32.0f);
    std::string filepath = "$(ProjectDir)/../Assets/wall/wall.obj";
    glm::mat4 shirneModelMatrix = glm::mat4(1.0f);
    shirneModelMatrix = glm::translate(shirneModelMatrix, glm::vec3(floorWidth / 2, 0, 0));
    shirneModelMatrix = glm::rotate(shirneModelMatrix, glm::radians(-90.0f), glm::vec3(0, 1, 0));
    shirneModelMatrix = glm::scale(shirneModelMatrix, glm::vec3(0.50f));
    Model shrineModel(shrineShader, camera, shirneModelMatrix, shrineMaterial, filepath, true);
    models.push_back(shrineModel);

    // Wall Model
    Shader wallShader("defaultShader.vs", "defaultShader.fs");
    Mesh wallMesh = MeshLibrary::planeMesh();
    wallMesh.addTextures("plaster.png", "nospecular.png");
    Material wallMaterial(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.3f), 32.0f);
    glm::mat4 wallModelMatrix = glm::mat4(1.0f);
    wallModelMatrix = wallModelMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0, wallHeight / 2, floorLength / 2));
    wallModelMatrix = wallModelMatrix * glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1, 0, 0));
    wallModelMatrix = wallModelMatrix * glm::scale(glm::mat4(1.0f), glm::vec3(floorWidth, 0.1f, wallHeight));
    Model staticWall(wallShader, camera, wallModelMatrix, wallMaterial, false);
    staticWall.addMesh(wallMesh);
    models.push_back(staticWall);

}
