#version 460 core
out vec4 FragColor;

in vec2 TexCoords;

uniform sampler2D colorTexture;

void main() {
  vec3 col  = texture(colorTexture, TexCoords).rgb;
  FragColor = vec4(col, 1.0);
}