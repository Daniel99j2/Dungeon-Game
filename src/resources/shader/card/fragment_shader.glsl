#version 430 core

in vec2 TexCoords;

uniform sampler2D tex;
uniform vec3 outlineColour;
uniform int flags;

out vec4 FragColor;

vec4 getColour();

void main() {
    FragColor = getColour();
    if(FragColor.a < 0.1) discard;
}

vec4 getColour() {
    if((flags & (1 << 0)) != 0) {
        vec4 texColour = texture(tex, TexCoords/2+vec2(0.5, 0.5));
        if(texColour.a > 0.1) {
            return texColour;
        }
    }
    if((flags & (1 << 1)) != 0) {
        vec4 texColour = texture(tex, TexCoords/2+vec2(0.5, 0));
        if(texColour.a > 0.1) {
            return texColour;
        }
    }

    vec4 outlineTexColour = texture(tex, TexCoords/2+vec2(0, 0.5));

    if(outlineTexColour.a > 0.1) return outlineTexColour*vec4(outlineColour, 1.0);
    return texture(tex, TexCoords/2);
}