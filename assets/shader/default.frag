#version 460 core
out vec4 FragColor;

struct Material {
  vec3  ambient;
  vec3  diffuse;
  vec3  specular;
  float shininess;
};

struct Light {
  vec3 position;
  vec3 ambient;
  vec3 diffuse;
  vec3 specular;
};

in vec2 texCoord;
in vec3 normal;
in vec3 fragPos;

uniform vec3 lightColor;
uniform vec3 objectColor;

uniform vec3 lightPos;
uniform vec3 viewPos;

uniform Material material;
uniform Light    light;

uniform sampler2D diffuseTexture;

void main() {
  vec3 ambient = light.ambient * vec3(texture(diffuseTexture, texCoord));

  vec3  norm     = normalize(normal);
  vec3  lightDir = normalize(lightPos - fragPos);
  float diff     = max(dot(norm, lightDir), 0.0f);
  vec3 diffuse = light.diffuse * diff * vec3(texture(diffuseTexture, texCoord));

  vec3 viewDir    = normalize(viewPos - fragPos);
  vec3 reflectDir = reflect(-lightDir, norm);

  float spec     = pow(max(dot(viewDir, reflectDir), 0.0f), material.shininess);
  vec3  specular = light.specular * (spec * material.specular);

  vec3 result = ambient + diffuse + specular;

  // FragColor   = texture(diffuseTexture, texCoord);
  FragColor = vec4(result, 1.0f);
}