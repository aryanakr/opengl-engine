/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "imgui/imgui.h"
#include "imgui/imgui_impl_glfw.h"
#include "imgui/imgui_impl_opengl3.h"

#include "Camera.h"
#include "LightSystem.h"
#include "PointLight.h"
#include "SpotLight.h"

#include "SGNode.h"
#include "TransformNode.h"
#include "NameNode.h"
#include "ModelNode.h"
#include "LightNode.h"

#include "Model.h"
#include "SceneGraphWindow.h"
#include "Helicopter.h"
#include "DirectionalLight.h"

#include "Table.h"
#include "Board.h"
#include "Room.h"
#include "SkyBox.h"
#include "Lamp.h"
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);


// settings
const unsigned int SCR_WIDTH = 1200;
const unsigned int SCR_HEIGHT = 800;

// camera
Camera camera(glm::vec3(-4.5f, 7.5f, -7.5f), glm::vec3(0, 1, 0),61.5f,-17.0f,(float)SCR_WIDTH/(float)SCR_HEIGHT);
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;

int main()
{
    // glfw initialize and configure
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Anilamp Assignment (Aryan Akbarpour)", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // Containers
    // -----------------------------------
    LightSystem lightSystem;
    vector<Model> models;
    vector<Model> staticModels;
    vector<SGNode*> objectRootNodes;

    // Initialize Scene
    // ------------------------------------
    // Create Lights
    Shader lightShader("defaultShader.vs", "lightSourceShader.fs");
    Material lightMaterial(glm::vec3(0.25f), glm::vec3(0.6f, 0.55f, 0.40f), glm::vec3(1.0f, 0.9f, 0.75f), 32.0f);

    // Create Room PointLight
    PointLight pointLight(lightShader, camera, glm::vec3(0.0f, 7.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), lightMaterial, "Room Light");
    pointLight.setAttenuationTerms(0.705f, 0.050f, 0.011f);

    // Create Sun
    Material sunMaterial(glm::vec3(0.1f), glm::vec3(0.40f, 0.35f, 0.25f), glm::vec3(1.0f, 0.9f, 0.75f), 32.0f);
    DirectionalLight directionalLight(lightShader, camera, glm::vec3(0.0f, 9.0f, 0.0f), glm::vec2(-55.0f, 20.0f), sunMaterial, "Sun");

    lightSystem.addlight(&directionalLight);
    lightSystem.addlight(&pointLight);
    
    // Create Skybox
    SkyBox skybox(camera);
    skybox.initialize();

    Lamp lamp;
    lamp.initialize(camera, models,objectRootNodes,lightSystem);

    Helicopter heli;
    heli.initialize(camera, models, objectRootNodes);

    Table table;
    table.initialize(camera, models, objectRootNodes);

    Board board;
    board.initialize(camera, models, objectRootNodes);

    Room room;
    room.initialize(camera, staticModels);

    lightSystem.initialize();
    // -----------------------------------------------
    // Initialize IMGUI
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    
    const char* glsl_version = "#version 330 core";
    ImGui_ImplOpenGL3_Init(glsl_version);

    // Imgui Control Variables
    SceneGraphWindow sceneGraphWindow;

    std::optional<int> selectedIndex;
    SGNode* pSelectedNode;
    
    std::optional<int> selectedLightIndex;
    Light* pSelectedLightNode;

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {

        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // window dimension update
        // ------
        int display_w, display_h;
        glfwGetFramebufferSize(window, &display_w, &display_h);
        camera.updateAspect((float)display_w / (float)display_h);

        // draw skybox
        // ------
        skybox.draw();

        // animations
        // ----------------------------------
        lamp.runAnimation();
        heli.runAnimation(lastFrame);

        // render scene
        // ----------------------------------
        lightSystem.render();

        for (auto& m : models) {
            lightSystem.setObjShader(m.getShader());
        }

        for (auto&& o : objectRootNodes) {
            o->draw();
        }
        for (auto&& sm : staticModels)
        {
            lightSystem.setObjShader(sm.getShader());
            sm.Draw();
        }

        // IMGUI 
        // ---------------------------------
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();

        // Create control windows 
        // ---------------------------------
        // scene graph window
        int nodeIndexTracker = 0;
        sceneGraphWindow.show(objectRootNodes, nodeIndexTracker, selectedIndex, pSelectedNode);

        // helicopter window
        heli.drawControlWindow();

        // lamp window
        lamp.drawControlWindow();

        // camera window
        camera.showCameraControlWindow();
        
        // light system window
        int lightIndexTracked = 0;
        lightSystem.showLightSystemControlWindow(lightIndexTracked, selectedLightIndex, pSelectedLightNode);

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    /*glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);*/

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        camera.ProcessKeyboard(Camera_Movement::UP, deltaTime);
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::DOWN, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::RIGHT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
        camera.ProcessKeyboard(Camera_Movement::BACKWARD, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
    if (firstMouse)
    {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;
    if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS)
        camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    camera.ProcessMouseScroll(yoffset);
}