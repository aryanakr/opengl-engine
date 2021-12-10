/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "Lamp.h"


Lamp::Lamp()
{
    MainRoot = nullptr;
    // initializing random values
    srand(time(0));
    for (int i = 0; i < 400; i++) {
        float randomnum = (float)rand() / RAND_MAX;
        randoms.push_back(randomnum);
    }
}

/**
  * @desc Create Lamp object
  * @param Camera& camera - scene camera refrence
           std::vector<Model>& models - main models vector refrence
           vector<SGNode*> roots - main root nodes vector refrence
*/
void Lamp::initialize(Camera& camera, vector<Model>& models, vector<SGNode*>& roots, LightSystem& lightSystem) 
{
    // Create Meshes
    Mesh lampCylinderMesh = MeshLibrary::cylinderMesh(0.5f, 0.5f, 1.0f, 32);
    lampCylinderMesh.addTextures("tigerlampbase.png", "container2_specular.png");
    Shader lampBodyShader("defaultShader.vs", "defaultShader.fs");
    Material lampBodyMaterial(glm::vec3(1.0f), glm::vec3(1.0f), glm::vec3(1.0f), 32.0f);
    Model lampBaseModel = Model(lampBodyShader, camera, glm::mat4(1), lampBodyMaterial, false);
    lampBaseModel.addMesh(lampCylinderMesh);
    models.push_back(lampBaseModel);

    Mesh lampCubeMesh = MeshLibrary::cubeMesh();
    lampCubeMesh.addTextures("Wood1.png", "Wood1_specular.png");
    Model lampCubeModel = Model(lampBodyShader, camera, glm::mat4(1), lampBodyMaterial, false);
    lampCubeModel.addMesh(lampCubeMesh);
    models.push_back(lampCubeModel);

    Mesh lampSphereMesh = MeshLibrary::sphereMesh();
    lampSphereMesh.addTextures("Wood1.png", "Wood1_specular.png");
    Model lampSphereModel = Model(lampBodyShader, camera, glm::mat4(1), lampBodyMaterial, false);
    lampSphereModel.addMesh(lampSphereMesh);
    models.push_back(lampSphereModel);

    Mesh lampBodyMesh = MeshLibrary::cylinderMesh(0.5f, 0.5f, 1.0f, 32);
    lampBodyMesh.addTextures("lampbody.png", "nospecular.png");
    Model lampBodyModel = Model(lampBodyShader, camera, glm::mat4(1), lampBodyMaterial, false);
    lampBodyModel.addMesh(lampBodyMesh);
    models.push_back(lampBodyModel);

    std::string filepath = "$(ProjectDir)/../Assets/lamphead/lamphead.obj";
    Model lampHeadModel(lampBodyShader, camera, glm::mat4(1.0f), lampBodyMaterial, filepath, true);
    models.push_back(lampHeadModel);

    filepath = "$(ProjectDir)/../Assets/tail/tail.obj";
    Model lampTailModel(lampBodyShader, camera, glm::mat4(1.0f), lampBodyMaterial, filepath, true);
    models.push_back(lampTailModel);

    filepath = "$(ProjectDir)/../Assets/hat/Cowboy_Hat_obj.obj";
    Model lampHatModel(lampBodyShader, camera, glm::mat4(1.0f), lampBodyMaterial, filepath, true);
    models.push_back(lampHatModel);

    // Creating Nodes Hierarchy

    SGNode* root = new NameNode("Lamp");
    glm::mat4 m(1);
    m = glm::translate(m, rootPos);
    m = glm::scale(m, rootScale);
    m = glm::rotate(m, glm::radians(20.0f), glm::vec3(0, 1, 0));

    SGNode* rootTransform = new TransformNode("Root (Transform)", m);
    SGNode* base = new NameNode("Base");
    m = glm::mat4(1);
    m = glm::scale(m, baseScale);
    SGNode* baseModelTransform = new TransformNode("Base Model (Trasnform)", m);
    SGNode* baseModel = new ModelNode("Base (Model)", lampBaseModel);


    SGNode* lowerJoint = new NameNode("Lower Joint");
    m = glm::mat4(1);
    m = glm::translate(m, lowerJointPos);
    m = glm::rotate(m, glm::radians(lowerJointAngX), glm::vec3(1, 0, 0));
    SGNode* lowerJointTransform = new TransformNode("Lower Joint (Transform)", m);
    m = glm::mat4(1);
    m = glm::scale(m, lowerJointModelScale);
    SGNode* lowerJointModelTransform = new TransformNode("Lower Joint Model (Transform)", m);
    SGNode* lowerJointModel = new ModelNode("Lower Joint (Model)", lampSphereModel);
    SGNode* lowerArm = new NameNode("Lower Arm");
    m = glm::mat4(1);
    m = glm::scale(m, lowerArmScale);
    SGNode* lowerArmTransform = new TransformNode("Lower Arm (Transform)", m);
    SGNode* lowerArmModel = new ModelNode("Lower Arm (Model)", lampBodyModel);
    //--------
    SGNode* middleJoint = new NameNode("Middle Joint");
    m = glm::mat4(1);
    m = glm::translate(m, middleJointPos);
    m = glm::rotate(m, glm::radians(middleJointAngX), glm::vec3(1, 0, 0));
    SGNode* middleJointTransform = new TransformNode("Middle Joint (Transform)", m);
    m = glm::mat4(1);
    m = glm::translate(m, middleJointModelPos);
    m = glm::scale(m, middleJointModelScale);
    m = glm::rotate(m, glm::radians(90.0f), glm::vec3(0, 0, 1));
    SGNode* middleJointModelTransform = new TransformNode("Middle Joint Model (Transform)", m);
    SGNode* middleJointModel = new ModelNode("Middle Joint (Model)", lampBaseModel);
    SGNode* upperArm = new NameNode("Upper Arm");
    m = glm::mat4(1);
    m = glm::scale(m, lowerArmScale);
    SGNode* upperArmTransform = new TransformNode("Upper Arm (Transform)", m);
    SGNode* upperArmModel = new ModelNode("Uppwer Arm (Model)", lampBodyModel);
    //---
    SGNode* upperJoint = new NameNode("Upper Joint");
    m = glm::mat4(1);
    m = glm::translate(m, upperJointPos);
    m = glm::rotate(m, glm::radians(upperJointAngX), glm::vec3(1, 0, 0));
    SGNode* upperJointTransform = new TransformNode("Upper Joint (Transform)", m);
    m = glm::mat4(1);
    m = glm::scale(m, lowerJointModelScale);
    SGNode* upperJointModelTransform = new TransformNode("Upper Joint Model (Transform)", m);
    SGNode* upperJointModel = new ModelNode("upper Joint (Model)", lampSphereModel);

    SGNode* head = new NameNode("Head");
    m = glm::mat4(1);
    m = glm::translate(m, headPos);
    m = glm::scale(m, headScale);
    m = glm::rotate(m, glm::radians(180.0f), glm::vec3(0, 1, 0));
    SGNode* headTransform = new TransformNode("Head (Transform)", m);
    SGNode* headModel = new ModelNode("Head (Model)", lampHeadModel);

    SGNode* hat = new NameNode("Hat");
    m = glm::mat4(1);
    m = glm::translate(m, hatPos);
    m = glm::scale(m, hatScale);
    m = glm::rotate(m, glm::radians(-80.0f), glm::vec3(1, 0, 0));
    SGNode* hatTransform = new TransformNode("Hat (Transform)", m);
    SGNode* hatModel = new ModelNode("Hat (Model)", lampHatModel);

    SGNode* tail = new NameNode("Tail");
    m = glm::mat4(1);
    m = glm::scale(m, tailScale);
    m = glm::rotate(m, glm::radians(90.0f), glm::vec3(0, 1, 0));
    SGNode* tailTransform = new TransformNode("Tail (Transform)", m);
    SGNode* tailModel = new ModelNode("Tail (Model)", lampTailModel);

    SGNode* light = new NameNode("Bulb");
    m = glm::mat4(1);
    m = glm::translate(m, bulbPos);
    m = glm::rotate(m, glm::radians(90.0f), glm::vec3(1, 0, 0));
    SGNode* lightTransform = new TransformNode("Bulb (Transform)", m);

    Shader lightShader("defaultShader.vs", "lightSourceShader.fs");
    Material lightMaterial(glm::vec3(0.1f), glm::vec3(0.5f), glm::vec3(1.0f), 32.0f);
    SpotLight spoot(lightShader, camera, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), lightMaterial, "Lamp Light", 0.92f, 0.90f);
    spoot.setAttenuationTerms(0.35f, 0.052f, 0.009f);
    spoot.setShowLightProp(false);
    Light* spotLight = new SpotLight(spoot);
    
    SGNode* lightNode = new LightNode("Light (SpotLight)", spotLight);

    lightSystem.addlight(spotLight);

    lightTransform->addChild(lightNode);
    light->addChild(lightTransform);
    upperJointTransform->addChild(light);

    tailTransform->addChild(tailModel);
    tail->addChild(tailTransform);
    middleJointTransform->addChild(tail);
    hatTransform->addChild(hatModel);
    hat->addChild(hatTransform);
    upperJointTransform->addChild(hat);
    headTransform->addChild(headModel);
    head->addChild(headTransform);
    upperJointTransform->addChild(head);
    upperJointModelTransform->addChild(upperJointModel);
    upperJointTransform->addChild(upperJointModelTransform);
    upperJoint->addChild(upperJointTransform);
    middleJointTransform->addChild(upperJoint);

    upperArmTransform->addChild(upperArmModel);
    upperArm->addChild(upperArmTransform);
    middleJointTransform->addChild(upperArm);
    middleJointModelTransform->addChild(middleJointModel);
    middleJointTransform->addChild(middleJointModelTransform);
    middleJoint->addChild(middleJointTransform);
    lowerJointTransform->addChild(middleJoint);
    lowerArmTransform->addChild(lowerArmModel);
    lowerArm->addChild(lowerArmTransform);
    lowerJointTransform->addChild(lowerArm);
    lowerJointModelTransform->addChild(lowerJointModel);
    lowerJointTransform->addChild(lowerJointModelTransform);
    lowerJoint->addChild(lowerJointTransform);
    base->addChild(lowerJoint);
    baseModelTransform->addChild(baseModel);
    base->addChild(baseModelTransform);
    rootTransform->addChild(base);
    root->addChild(rootTransform);

    root->update();

    MainRoot = root;
    roots.push_back(root);

}

/**
  * @desc draw imgui lamp controller window
*/
void Lamp::drawControlWindow()
{
    if (ImGui::Begin("Lamp Control Window"))
    {
        // Button to move to random pose
        if (ImGui::Button("Random Pose"))
        {
            if (!isAnimationRunning)
            {
                creatNewTarget();
                isAnimationRunning = true;

                randomOffset += 5;
                if (randomOffset + 4 > randoms.size())
                    randomOffset = 0;
            }

        }
        // Button to go back to initial pose
        if (ImGui::Button("Reset"))
        {
            if (!isAnimationRunning)
            {
                setResetTarget();
                isAnimationRunning = true;
            }
        }

        // Manual control pose
        ImGui::Text("Joint Controls");
        ImGui::Text("Lower Joint");
        ImGui::SliderFloat("Pitch##LowerJoint", &sliderLowerX, lowerJointXMin, lowerJointXMax);
        ImGui::SliderFloat("Yaw##LowerJoint", &sliderlowerY, lowerJointYMin, lowerJointYMax);
        ImGui::Text("Middle Joint");
        ImGui::SliderFloat("Pitch##MiddleJoint", &slidermiddleX, middleJointXMin, middleJointXMax);
        ImGui::Text("Upper Joint");
        ImGui::SliderFloat("Pitch##UpperJoint", &sliderupperX, upperJointXMin, upperJointXMax);

        if (ImGui::Button("Apply"))
        {
            if (!isAnimationRunning) {
                lowerJointAngX = floor(sliderLowerX);
                lowerJointAngY = floor(sliderlowerY);
                middleJointAngX = floor(slidermiddleX);
                upperJointAngX = floor(sliderupperX);
                updateJointsTransforms();

            }
        }
        if (ImGui::Button("Set as Target"))
        {
            if (!isAnimationRunning) {
                lowerJointXTarget = floor(sliderLowerX);
                lowerJointYTarget = floor(sliderlowerY);
                middleJointXTarget = floor(slidermiddleX);
                upperJointXTarget = floor(sliderupperX);
                isAnimationRunning = true;

            }
        }
    }
    ImGui::End();
}

/**
  * @desc process lamp animations
*/
void Lamp::runAnimation()
{
    if (isAnimationRunning)
    {
        if (lowerJointAngX == lowerJointXTarget && lowerJointAngY == lowerJointYTarget
            && middleJointAngX == middleJointXTarget && upperJointAngX == upperJointXTarget)
        {
            isAnimationRunning = false;
            return;
        }



        // lower X
        if (lowerJointAngX > lowerJointXTarget)
        {
            lowerJointAngX -= 1.0f;
        }
        else if (abs(lowerJointXTarget - lowerJointAngX) > 0.30f)
        {
            lowerJointAngX += 1.0f;
        }

        //lower Y
        if (lowerJointAngY > lowerJointYTarget)
        {
            lowerJointAngY -= 1.0f;
        }

        else if (abs(lowerJointYTarget - lowerJointAngY) > 0.30f)
        {
            lowerJointAngY += 1.0f;
        }

        // middle X
        if (middleJointAngX > middleJointXTarget)
        {
            middleJointAngX -= 1.0f;
        }
        else if (abs(middleJointXTarget - middleJointAngX) > 0.30f)
        {
            middleJointAngX += 1.0f;
        }

        // upper X
        if (upperJointAngX > upperJointXTarget)
        {
            upperJointAngX -= 1.0f;
        }
        else if (abs(upperJointXTarget - upperJointAngX) > 0.30f)
        {
            upperJointAngX += 1.0f;
        }

        updateJointsTransforms();



    }

}

/**
  * @desc create targets for a random pose
*/
void Lamp::creatNewTarget()
{
    float newtarget = floor(randoms[randomOffset] * (lowerJointXMax - lowerJointXMin) + lowerJointXMin);


    if (newtarget > lowerJointXMax)
        newtarget = lowerJointXMax;
    else if (newtarget < lowerJointXMin)
        newtarget = lowerJointXMin;
    lowerJointXTarget = newtarget;

    newtarget = floor(randoms[randomOffset + 1] * (lowerJointYMax - lowerJointYMin) + lowerJointYMin);
    if (newtarget > lowerJointYMax)
        newtarget = lowerJointYMax;
    else if (newtarget < lowerJointYMin)
        newtarget = lowerJointYMin;
    lowerJointYTarget = newtarget;

    newtarget = floor(randoms[randomOffset + 2] * (middleJointXMax - middleJointXMin) + middleJointXMin);
    if (newtarget > middleJointXMax)
        newtarget = middleJointXMax;
    else if (newtarget < middleJointXMin)
        newtarget = middleJointXMin;
    middleJointXTarget = newtarget;

    newtarget = floor(randoms[randomOffset + 3] * (upperJointXMax - upperJointXMin) + upperJointXMin);
    if (newtarget > upperJointXMax)
        newtarget = upperJointXMax;
    else if (newtarget < upperJointXMin)
        newtarget = upperJointXMin;
    upperJointXTarget = newtarget;
}

/**
  * @desc set target to initial pose
*/
void Lamp::setResetTarget()
{
    lowerJointXTarget = initialLowerJointAngX;
    lowerJointYTarget = initiallowerJointAngY;
    middleJointXTarget = initialMiddleJointAngX;
    upperJointXTarget = initialupperJointAngX;
}

void Lamp::printTarget()
{
    std::cout << "Lower Joint With Target X : " << lowerJointXTarget << " Y : " << lowerJointYTarget << std::endl;
    std::cout << "Middle Joint With Target X : " << middleJointXTarget << std::endl;
    std::cout << "Upper Joint With Target X : " << upperJointXTarget << std::endl;
}

void Lamp::printCurrent()
{
    std::cout << "Lower Joint With Angle X : " << lowerJointAngX << " Y : " << lowerJointAngY << std::endl;
    std::cout << "Middle Joint With Angle X : " << middleJointAngX << std::endl;
    std::cout << "Upper Joint With Angle X : " << upperJointAngX << std::endl;
}

/**
  * @desc update transforms of important nodes
*/
void Lamp::updateJointsTransforms()
{
    glm::mat4 m = glm::mat4(1);
    m = glm::translate(m, lowerJointPos);
    m = glm::rotate(m, glm::radians(lowerJointAngX), glm::vec3(1, 0, 0));
    m = glm::rotate(m, glm::radians(lowerJointAngY), glm::vec3(0, 1, 0));
    MainRoot->setTransformByName("Lower Joint (Transform)", m);

    m = glm::mat4(1);
    m = glm::translate(m, middleJointPos);
    m = glm::rotate(m, glm::radians(middleJointAngX), glm::vec3(1, 0, 0));
    MainRoot->setTransformByName("Middle Joint (Transform)", m);

    m = glm::mat4(1);
    m = glm::translate(m, upperJointPos);
    m = glm::rotate(m, glm::radians(upperJointAngX), glm::vec3(1, 0, 0));
    MainRoot->setTransformByName("Upper Joint (Transform)", m);

    MainRoot->update();
}