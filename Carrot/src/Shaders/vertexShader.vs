#version 460 core

layout (location = 0) in vec3 a_Position;

out vec3 v_Position;

uniform mat4 ProjectionViewMatrix;
uniform mat4 ModelMatrix;

void main(){
    v_Position = a_Position;
    gl_Position = ProjectionViewMatrix*ModelMatrix*vec4(a_Position,1.0);
}