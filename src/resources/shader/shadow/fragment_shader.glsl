#version 430 core

in vec2 TexCoords;

uniform sampler2D tex;
uniform vec2 screenSize;

layout(std430, binding = 0) buffer ShadowData {
    int distances[360];
} shadowData;

void main() {
    if(texture(tex, TexCoords).a >= 0.1) {
        vec2 dir = gl_FragCoord.xy - screenSize / 2;

        int angle = int(floor(degrees(atan(dir.y, dir.x)))) + 180;

        atomicMin(shadowData.distances[angle], int(length(dir)));
    };

    discard;
}