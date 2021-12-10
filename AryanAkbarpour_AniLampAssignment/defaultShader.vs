/**
  * This file is part of COM3503 assignment
  *
  * I declare that this code is my own work
  * Author Aryan Akbarpour aakbarpour1@sheffield.ac.uk
*/
#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec3 inNormal;
layout (location = 2) in vec2 inTexCoord;

out vec3 Normal;
out vec2 TexCoord;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {

  mat4 mvpMatrix = projection * view * model;
  
  gl_Position = mvpMatrix * vec4(position, 1.0);

  FragPos = vec3(model * vec4(position, 1.0));
  // inverse operation is costly for gpu so it needs to be send to cpu
  Normal =  mat3(transpose(inverse(model))) * inNormal;  
  TexCoord = inTexCoord;
}