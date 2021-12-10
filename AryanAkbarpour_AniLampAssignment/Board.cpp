/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "Board.h"

Board::Board()
{}

Board::~Board()
{}

/**
  * @desc Create models and node hierarchy of the board
  * @param Camera& camera - scene camera refrence
           vector<Model>& models - main models vector refrence
           vector<SGNode*>& roots - main root nodes vector refrence
*/
void Board::initialize(Camera& camera, std::vector<Model>& models, std::vector<SGNode*>& roots)
{
    // create static models
    // -------------------------
    Shader boardShader("defaultShader.vs", "defaultShader.fs");
    // Frame Cube Model
    Mesh frameMesh = MeshLibrary::cubeMesh();
    frameMesh.addTextures("metal2.png", "metal2_specular.png");
    Material frameMaterial(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.80f), 64.0f);
    Model frameModel = Model(boardShader, camera, glm::mat4(1.0f), frameMaterial, false);
    frameModel.addMesh(frameMesh);
    models.push_back(frameModel);

    // Board Cube Model
    Mesh boardMesh = MeshLibrary::cubeMesh();
    boardMesh.addTextures("noticeboard.jpg", "nospecular.png");
    Material boardMaterial(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.5f), 0.0f);
    Model boardModel = Model(boardShader, camera, glm::mat4(1.0f), frameMaterial, false);
    boardModel.addMesh(boardMesh);
    models.push_back(boardModel);

    // Picture Models
    Material pictureMaterial(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(0.60f), 64.0f);
    // picture 1
    Mesh picture1Mesh = MeshLibrary::planeMesh();
    picture1Mesh.addTextures("picture1.jpg", "picutre_specular.png");
    Model picture1Model = Model(boardShader, camera, glm::mat4(1.0f), pictureMaterial, false);
    picture1Model.addMesh(picture1Mesh);
    models.push_back(picture1Model);
    // picture 2
    Mesh picture2Mesh = MeshLibrary::planeMesh();
    picture2Mesh.addTextures("picture2.png", "picutre_specular.png");
    Model picture2Model = Model(boardShader, camera, glm::mat4(1.0f), pictureMaterial, false);
    picture2Model.addMesh(picture2Mesh);
    models.push_back(picture2Model);
    // picture 3
    Mesh picture3Mesh = MeshLibrary::planeMesh();
    picture3Mesh.addTextures("picture3.png", "picutre_specular.png");
    Model picture3Model = Model(boardShader, camera, glm::mat4(1.0f), pictureMaterial, false);
    picture3Model.addMesh(picture3Mesh);
    models.push_back(picture3Model);

    // create node hierarchy
    glm::vec3 frameHorizentalScale = glm::vec3(boardScale.x, boardScale.y + frameDepth, frameWidth);
    glm::vec3 frameverticalScale = glm::vec3(frameWidth, boardScale.y + frameDepth, boardScale.z + frameWidth);

    SGNode* rootNode = new NameNode("Notice Board");
    glm::mat4 m(1);
    m = glm::translate(m, rootPos);
    m = glm::rotate(m, glm::radians(-90.0f), glm::vec3(1, 0, 0));
    SGNode* rootTransform = new TransformNode("Root (Transform)", m);

    SGNode* frame = new NameNode("Frame");
    // top
    m = glm::mat4(1);
    m = glm::translate(m, glm::vec3(0.0f, 0.0f, boardScale.z / 2.0f));
    m = glm::scale(m, frameHorizentalScale);
    SGNode* frameTopTransform = new TransformNode("Frame Top (Trasnform)", m);
    SGNode* frameTopModelNode = new ModelNode("Frame Top (Model)", frameModel);
    // bottom
    m = glm::mat4(1);
    m = glm::translate(m, glm::vec3(0.0f, 0.0f, -boardScale.z / 2.0f));
    m = glm::scale(m, frameHorizentalScale);
    SGNode* frameBottomTransform = new TransformNode("Frame Bottom (Trasnform)", m);
    SGNode* frameBottomModelNode = new ModelNode("Frame Bottom (Model)", frameModel);
    // left
    m = glm::mat4(1);
    m = glm::translate(m, glm::vec3(boardScale.x / 2.0f, 0.0f, 0.0f));
    m = glm::scale(m, frameverticalScale);
    SGNode* frameLeftTransform = new TransformNode("Frame Left (Trasnform)", m);
    SGNode* frameLeftModelNode = new ModelNode("Frame Left (Model)", frameModel);
    // right
    m = glm::mat4(1);
    m = glm::translate(m, glm::vec3(-boardScale.x / 2.0f, 0.0f, 0.0f));
    m = glm::scale(m, frameverticalScale);
    SGNode* frameRightTransform = new TransformNode("Frame Right (Trasnform)", m);
    SGNode* frameRightModelNode = new ModelNode("Frame Right (Model)", frameModel);


    SGNode* board = new NameNode("Board");
    m = glm::mat4(1);
    m = glm::scale(m, boardScale);
    SGNode* boardTransform = new TransformNode("Board (Trasnform)", m);
    SGNode* boardModelNode = new ModelNode("Board (Model)", boardModel);

    SGNode* picture1 = new NameNode("Picture 1");
    m = glm::mat4(1);
    m = glm::translate(m, pic1Pos);
    m = glm::scale(m, pic1Scale);
    SGNode* picture1Transform = new TransformNode("Picture 1 (Trasnform)", m);
    SGNode* picture1ModelNode = new ModelNode("Picture 1 (Model)", picture1Model);

    SGNode* picture2 = new NameNode("Picture 2");
    m = glm::mat4(1);
    m = glm::translate(m, pic2Pos);
    m = glm::scale(m, pic2Scale);
    m = glm::rotate(m, glm::radians(7.0f), glm::vec3(0, 1, 0));
    SGNode* picture2Transform = new TransformNode("Picture 2 (Trasnform)", m);
    SGNode* picture2ModelNode = new ModelNode("Picture 2 (Model)", picture2Model);

    SGNode* picture3 = new NameNode("Picture 3");
    m = glm::mat4(1);
    m = glm::translate(m, pic3Pos);
    m = glm::scale(m, pic3Scale);
    m = glm::rotate(m, glm::radians(-12.0f), glm::vec3(0, 1, 0));

    SGNode* picture3Transform = new TransformNode("Picture 3 (Trasnform)", m);
    SGNode* picture3ModelNode = new ModelNode("Picture 3 (Model)", picture3Model);

    
    boardTransform->addChild(boardModelNode);
    board->addChild(boardTransform);
    rootTransform->addChild(board);
    frameRightTransform->addChild(frameRightModelNode);
    frame->addChild(frameRightTransform);
    frameLeftTransform->addChild(frameLeftModelNode);
    frame->addChild(frameLeftTransform);
    frameBottomTransform->addChild(frameBottomModelNode);
    frame->addChild(frameBottomTransform);
    frameTopTransform->addChild(frameTopModelNode);
    frame->addChild(frameTopTransform);
    rootTransform->addChild(frame);
    picture1Transform->addChild(picture1ModelNode);
    picture1->addChild(picture1Transform);
    rootTransform->addChild(picture1);
    picture2Transform->addChild(picture2ModelNode);
    picture2->addChild(picture2Transform);
    rootTransform->addChild(picture2);
    picture3Transform->addChild(picture3ModelNode);
    picture3->addChild(picture3Transform);
    rootTransform->addChild(picture3);
    rootNode->addChild(rootTransform);

    rootNode->update();

    root = rootNode;
    roots.push_back(rootNode);
}

