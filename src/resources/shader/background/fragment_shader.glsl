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

    if(shadow[angle] < length(dir)) FragColor = vec4((FragColor.rgb *= 0.5f), FragColor.a);
    //else FragColor.g = 1;

    //FragColor = vec4(gl_FragCoord.xy / screenSize, 1.0, 1.0);
}