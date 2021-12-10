/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#include "Camera.h"

// constructor with vectors
Camera::Camera(float aspect)
    :
    Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM),
    Position(glm::vec3(0.0f, 0.0f, 0.0f)),
    WorldUp(glm::vec3(0.0f, 1.0f, 0.0f)),
    Yaw(YAW),
    Pitch(PITCH),
    aspect(aspect)
{
    updateCameraVectors();
}
// constructor with scalar values
Camera::Camera(glm::vec3 pos, glm::vec3 worldUp, float yaw, float pitch, float aspect)
    : 
    Front(glm::vec3(0.0f, 0.0f, -1.0f)),
    MovementSpeed(SPEED),
    MouseSensitivity(SENSITIVITY),
    Zoom(ZOOM),
    aspect(aspect)
{
    Position = pos;
    WorldUp = worldUp;
    Yaw = yaw;
    Pitch = pitch;
    updateCameraVectors();
}

// returns the view matrix calculated using Euler Angles and the LookAt Matrix
glm::mat4 Camera::GetViewMatrix()
{
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Camera::GetProjectionMatrix()
{
    glm::mat4 projection = glm::perspective(glm::radians(Zoom), aspect, 0.1f, 100.0f);
    return projection;
}

void Camera::updateAspect(float a)
{
    aspect = a;
}

// processes input received from any keyboard-like input system. Accepts input parameter in the form of camera defined ENUM (to abstract it from windowing systems)
void Camera::ProcessKeyboard(Camera_Movement direction, float deltaTime)
{
    float velocity = MovementSpeed * deltaTime;
    if (direction == Camera_Movement::FORWARD)
        Position += Front * velocity;
    if (direction == Camera_Movement::BACKWARD)
        Position -= Front * velocity;
    if (direction == Camera_Movement::LEFT)
        Position -= Right * velocity;
    if (direction == Camera_Movement::RIGHT)
        Position += Right * velocity;
    if (direction == Camera_Movement::UP)
        Position += Up * velocity;
    if (direction == Camera_Movement::DOWN)
        Position -= Up * velocity;
}

// processes input received from a mouse input system. Expects the offset value in both the x and y direction.
void Camera::ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch)
{
    xoffset *= MouseSensitivity;
    yoffset *= MouseSensitivity;

    Yaw += xoffset;
    Pitch += yoffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (constrainPitch)
    {
        if (Pitch > 89.0f)
            Pitch = 89.0f;
        if (Pitch < -89.0f)
            Pitch = -89.0f;
    }

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVectors();
}

// processes input received from a mouse scroll-wheel event. Only requires input on the vertical wheel-axis
void Camera::ProcessMouseScroll(float yoffset)
{
    Zoom -= (float)yoffset;
    if (Zoom < 1.0f)
        Zoom = 1.0f;
    if (Zoom > 45.0f)
        Zoom = 45.0f;
}

void Camera::showCameraControlWindow()
{
    if (ImGui::Begin("Camera Control Window")) {
        ImGui::BulletText(
            "Use keyboard keys up, down, left and right for panning.\n"
            "To rotate use mouse RIGHT! click and drag.\n"
            "Use keyboard A and Z to move camera in forward and backward direction respectively.\n"
            "Use Mouse Scroll to zoom."
        );
        ImGui::Separator();
        float* posFloat3[3] = { &Position.x, &Position.y, &Position.z };
        ImGui::SliderFloat3("Position", *posFloat3, -10.0f, 10.0f, "%.01f");
        ImGui::SliderFloat("Yaw", &Yaw, -180.0f, 180.0f, "%.1f");
        ImGui::SliderFloat("Pitch", &Pitch, -180.0f, 180.0f, "%.1f");
        ImGui::SliderFloat("Zoom", &Zoom, -1.0f, 45, "%.1f");
        updateCameraVectors();
    }
    ImGui::End();
}

// calculates the front vector from the Camera's (updated) Euler Angles
void Camera::updateCameraVectors()
{
    // calculate the new Front vector
    glm::vec3 front;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(front);
    // also re-calculate the Right and Up vector
    Right = glm::normalize(glm::cross(Front, WorldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    Up = glm::normalize(glm::cross(Right, Front));
}
