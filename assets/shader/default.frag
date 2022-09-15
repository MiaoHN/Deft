#version 460 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D textureDiffuse;

void main() { FragColor = texture(textureDiffuse, texCoord); }