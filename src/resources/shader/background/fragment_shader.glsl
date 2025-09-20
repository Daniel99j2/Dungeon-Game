#version 330 core

in vec2 TexCoords;
in vec4 VertexPos;

uniform sampler2D tex;

out vec4 FragColor;

void main() {
    FragColor = vec4(vec3(texture(tex, TexCoords)), 1.0);
    if(FragColor.a == 0) discard;
}