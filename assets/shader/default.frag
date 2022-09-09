#version 460 core
out vec4 FragColor;

in vec2 texCoord;

uniform sampler2D diffuseTexture;

void main() { FragColor = texture(diffuseTexture, texCoord); }