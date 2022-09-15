#version 460 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aTexCoord;

out vec2 texCoord;
out vec3 normal;

layout(std140, binding = 0) uniform camera {
  mat4 viewProjection;
  vec3 cameraPosition;
};

uniform mat4 model;

void main() {
  gl_Position = viewProjection * model * vec4(aPos, 1.0f);
  texCoord    = aTexCoord;
  normal      = aNormal;
  // normal      = mat3(transpose(inverse(model))) * aNormal;
}