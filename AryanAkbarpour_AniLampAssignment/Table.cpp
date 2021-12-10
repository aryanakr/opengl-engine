/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "Table.h"

Table::Table()
{
	rootNode = nullptr;
}

Table::~Table()
{
}

/**
  * @desc Create a node hierarcy of a table
  * @param Camera& camera - scene camera refrence
  *        std::vector<Model>& models - main models vector refrences
  *        std::vector<SGNode*>& roots - main root nodes vector refrence 
*/
void Table::initialize(Camera& camera, std::vector<Model>& models, std::vector<SGNode*>& roots)
{
    Mesh tableSurfaceMesh = MeshLibrary::cubeMesh();
    tableSurfaceMesh.addTextures("Wood1.png", "Wood1_specular.png");
    Shader tableShader("defaultShader.vs", "defaultShader.fs");
    Material tableSurfaceMaterial(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), 32.0f);
    Model tableSurfaceModel = Model(tableShader, camera, glm::mat4(1), tableSurfaceMaterial, false);
    tableSurfaceModel.addMesh(tableSurfaceMesh);
    models.push_back(tableSurfaceModel);

    Mesh tableLegMesh = MeshLibrary::cylinderMesh(0.3f, 0.5f, 1.0f, 32);
    tableLegMesh.addTextures("metal1.png", "metal1_specualr.png");
    Material tableLegMaterial(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), 32.0f);
    Model tableLegModel = Model(tableShader, camera, glm::mat4(1), tableLegMaterial, false);
    tableLegModel.addMesh(tableLegMesh);
    models.push_back(tableLegModel);

    // Prop Models
    Shader tablePropShader("defaultShader.vs", "defaultShader.fs");
    Material propMaterial(glm::vec3(1.0f), glm::vec3(0.882, 0.866, 0.8), glm::vec3(0.5f, 0.5f, 0.5f), 32.0f);
    std::string pfilepath = "$(ProjectDir)/../Assets/pencil/pencil.obj";
    Model pencilModel(tablePropShader, camera, glm::mat4(1.0f), propMaterial, pfilepath, true);
    models.push_back(pencilModel);

    Mesh paperMesh = MeshLibrary::planeMesh();
    paperMesh.addTextures("paper.png", "Wood1_specular.png");
    Model paperModel = Model(tablePropShader, camera, glm::mat4(1), propMaterial, false);
    paperModel.addMesh(paperMesh);
    models.push_back(paperModel);

    // Create Table SGNode Hierarchy
    

    SGNode* tableRoot_Node = new NameNode("Table");
    glm::mat4 tableTransformModelMatrix(1.0f);
    tableTransformModelMatrix = tableTransformModelMatrix * glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, floorLength / 2 - tableDepth / 2));
    tableTransformModelMatrix = tableTransformModelMatrix * glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0, 1, 0));
    SGNode* tableTransform_Node = new TransformNode("Root Transform", tableTransformModelMatrix);
    SGNode* tableSurface_Node = new NameNode("Surface");

    glm::mat4 m = glm::translate(glm::mat4(1), glm::vec3(0, tableLegHeight + (tableThickness / 2), 0));
    m = m * glm::scale(glm::mat4(1), glm::vec3(tableDepth, tableThickness, tableWidth));
    SGNode* surfaceTransform_Node = new TransformNode("Surface Transform", m);
    SGNode* surfaceShape_Node = new ModelNode("SurfaceModel(Surface)", tableSurfaceModel);

    SGNode* leg1_Node = new NameNode("Leg 1");
    m = glm::mat4(1);
    m = m * glm::translate(glm::mat4(1), glm::vec3(-(tableDepth / 2.0f - tableLegWidth / 2.0f), 0, -(tableWidth / 2.0f - tableLegWidth / 2.0f)));
    m = m * glm::scale(glm::mat4(1), glm::vec3(tableLegWidth, tableLegHeight, tableLegWidth));
    SGNode* leg1Transform_Node = new TransformNode("Leg 1 Transform", m);
    SGNode* leg1Shape_Node = new ModelNode("LegModel(Leg 1)", tableLegModel);

    SGNode* leg2_Node = new NameNode("Leg 2");
    m = glm::mat4(1);
    m = m * glm::translate(glm::mat4(1), glm::vec3((tableDepth / 2.0f - tableLegWidth / 2.0f), 0, (tableWidth / 2.0f - tableLegWidth / 2.0f)));
    m = m * glm::scale(glm::mat4(1), glm::vec3(tableLegWidth, tableLegHeight, tableLegWidth));
    SGNode* leg2Transform_Node = new TransformNode("Leg 2 transform", m);
    SGNode* leg2Shape_Node = new ModelNode("LegModel(Leg 2)", tableLegModel);

    SGNode* leg3_Node = new NameNode("Leg 3");
    m = glm::mat4(1);
    m = m * glm::translate(glm::mat4(1), glm::vec3((tableDepth / 2.0f - tableLegWidth / 2.0f), 0, -(tableWidth / 2.0f - tableLegWidth / 2.0f)));
    m = m * glm::scale(glm::mat4(1), glm::vec3(tableLegWidth, tableLegHeight, tableLegWidth));
    SGNode* leg3Transform_Node = new TransformNode("Leg 3 transform", m);
    SGNode* leg3Shape_Node = new ModelNode("LegModel(Leg 3)", tableLegModel);

    SGNode* leg4_Node = new NameNode("Leg 4");
    m = glm::mat4(1);
    m = m * glm::translate(glm::mat4(1), glm::vec3(-(tableDepth / 2.0f - tableLegWidth / 2.0f), 0, (tableWidth / 2.0f - tableLegWidth / 2.0f)));
    m = m * glm::scale(glm::mat4(1), glm::vec3(tableLegWidth, tableLegHeight, tableLegWidth));
    SGNode* leg4Transform_Node = new TransformNode("Leg 4 transform", m);
    SGNode* leg4Shape_Node = new ModelNode("LegModel(Leg 4)", tableLegModel);

    // Create Table Props Nodes
    SGNode* pencil_Node = new NameNode("Pencil");
    m = glm::mat4(1);
    m = m * glm::translate(glm::mat4(1.0f), glm::vec3(0.803f, 2.75f, -0.57f));
    m = m * glm::rotate(glm::mat4(1.0f), glm::radians(-55.0f), glm::vec3(0, 1, 0));
    m = m * glm::scale(glm::mat4(1.0f), glm::vec3(0.042f));
    SGNode* pencilTransform_Node = new TransformNode("Pencil Transform", m);
    SGNode* pencilModel_Node = new ModelNode("Model(Pencil)", pencilModel);

    SGNode* paper_Node = new NameNode("Paper");
    m = glm::mat4(1);
    m = m * glm::translate(glm::mat4(1.0f), glm::vec3(1.03f, 2.72f, 0.40f));
    m = m * glm::rotate(glm::mat4(1.0f), glm::radians(-81.0f), glm::vec3(0, 1, 0));
    m = m * glm::rotate(glm::mat4(1.0f), glm::radians(180.0f), glm::vec3(0, 0, 1));
    m = m * glm::scale(glm::mat4(1.0f), glm::vec3(1.4f, -1.0f, 2.0f));
    SGNode* paperTransform_Node = new TransformNode("Paper Transform", m);
    SGNode* paperlModel_Node = new ModelNode("Model(Paper)", paperModel);


    paperTransform_Node->addChild(paperlModel_Node);
    paper_Node->addChild(paperTransform_Node);
    tableSurface_Node->addChild(paper_Node);
    pencilTransform_Node->addChild(pencilModel_Node);
    pencil_Node->addChild(pencilTransform_Node);
    tableSurface_Node->addChild(pencil_Node);

    leg4Transform_Node->addChild(leg4Shape_Node);
    leg4_Node->addChild(leg4Transform_Node);
    tableSurface_Node->addChild(leg4_Node);
    leg3Transform_Node->addChild(leg3Shape_Node);
    leg3_Node->addChild(leg3Transform_Node);
    tableSurface_Node->addChild(leg3_Node);
    leg2Transform_Node->addChild(leg2Shape_Node);
    leg2_Node->addChild(leg2Transform_Node);
    tableSurface_Node->addChild(leg2_Node);
    leg1Transform_Node->addChild(leg1Shape_Node);
    leg1_Node->addChild(leg1Transform_Node);
    tableSurface_Node->addChild(leg1_Node);
    surfaceTransform_Node->addChild(surfaceShape_Node);
    tableSurface_Node->addChild(surfaceTransform_Node);
    tableTransform_Node->addChild(tableSurface_Node);
    tableRoot_Node->addChild(tableTransform_Node);

    tableRoot_Node->update();

    rootNode = tableRoot_Node;
    roots.push_back(tableRoot_Node);
}
