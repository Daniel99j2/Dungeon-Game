#version 330 core
out vec4 FragColor;

in vec2 TexCoords;
uniform float gamma;
uniform float exposure;
uniform sampler2D hdrBuffer;

void main() {
    vec3 hdrColor = texture(hdrBuffer, TexCoords).rgb;
    vec3 result = vec3(1.0) - exp(-hdrColor * exposure);
    result = pow(result, vec3(1.0 / gamma));
    FragColor = vec4(result, 1.0);
}