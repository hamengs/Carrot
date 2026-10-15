#version 460 core

in vec3 v_Position;

layout(location = 0) out vec4 color;

void main(){

    color = vec4(v_Position*0.5+0.5,1.0);
}