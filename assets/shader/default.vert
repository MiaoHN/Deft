#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 texCoord;
out vec3 normal;
out vec3 fragPos;

uniform mat4 transform;
uniform mat4 model;

void main() {
  gl_Position = transform * vec4(aPos, 1.0f);
  fragPos     = vec3(model * vec4(aPos, 1.0f));
  texCoord    = aTexCoord;
  normal      = aNormal;
  // normal      = mat3(transpose(inverse(model))) * aNormal;
}