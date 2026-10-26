#version 460 core

in vec3 v_Position;
in vec2 v_TexCoord;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(){

    color = texture(u_Texture, v_TexCoord) * u_Color;

}