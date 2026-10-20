#version 460 core

in vec3 v_Position;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;

void main(){

    color = u_Color;
}