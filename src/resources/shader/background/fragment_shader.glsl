#version 430 core

in vec2 TexCoords;

uniform sampler2D tex;
uniform vec2 screenSize;

uniform int[360] shadow;

out vec4 FragColor;

void main() {
    FragColor = texture(tex, TexCoords);
    if(FragColor.a < 0.1) discard;
    vec2 dir = gl_FragCoord.xy - screenSize / 2;

    int angle = int(floor(degrees(atan(dir.y, dir.x)))) + 180;

    vec3 outColour = vec3(FragColor);
    if(shadow[angle] < (length(dir) * 10000) - 50000) outColour *= 0.5f;

    outColour *= 1-length(gl_FragCoord.xy/screenSize-0.5);

    FragColor = vec4(outColour, FragColor.a);
    //else FragColor.g = 1;

    //FragColor = vec4(gl_FragCoord.xy / screenSize, 1.0, 1.0);
}