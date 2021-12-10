/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * This file contains codes from online tutorial
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#pragma once
#ifndef MODEL_H
#define MODEL_H

#include "Mesh.h"
#include "Shader.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Material.h"
#include "Camera.h"

class Model
{
public:
    Model() = default;
    Model(Shader& shader, Camera& camera, glm::mat4 modelMatrix, Material material, bool gamma);
    Model(Shader& shader, Camera& camera, glm::mat4 modelMatrix, Material material, string const& path, bool gamma);

    void addMesh(Mesh& mesh);
    void Draw(glm::mat4 m);
    void Draw();
    void setModelMatrix(glm::mat4 m);
    void setCamera(Camera& camera);

    Shader& getShader();
    glm::mat4 getModelMatrix();
    Material& getMaterial();
    Shader shader;
    glm::mat4 modelMatrix;

protected:
    // model data
    
    Material material;
    Camera& camera;

    vector<Mesh> meshes;
    vector<Texture> textures_loaded;
    string directory;
    bool gammaCorrection;

    void loadModel(string path);
    void processNode(aiNode* node, const aiScene* scene);
    Mesh processMesh(aiMesh* mesh, const aiScene* scene);
    vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, string typeName);
};
#endif
