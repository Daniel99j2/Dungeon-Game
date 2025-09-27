#version 430 core

in vec2 TexCoords;

uniform sampler2D tex;

out vec4 FragColor;

void main() {
    FragColor = texture(tex, TexCoords);
    if(FragColor.a < 0.1) discard;
}