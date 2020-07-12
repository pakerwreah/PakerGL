#version 330 core

in vec2 texCoord;

uniform vec4 u_color;
uniform sampler2D u_texture;

out vec4 fragColor;

void main() {
    if (texCoord.x >= 0) {
        fragColor = texture(u_texture, texCoord);
    } else {
        fragColor = u_color;
    }
}