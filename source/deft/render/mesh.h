#ifndef __DEFT_MESH_H__
#define __DEFT_MESH_H__

#include <memory>
#include <unordered_map>
#include <vector>

#include "ecs/ecs.h"
#include "render/index_buffer.h"
#include "render/shader.h"
#include "render/texture.h"
#include "render/vertex_array.h"
#include "render/vertex_buffer.h"

namespace deft {

enum class TextureType {
  Diffuse = 0,
  Specular,
};

class Mesh {
 public:
  Mesh();
  Mesh(const std::vector<float>&         vertices,
       const std::vector<BufferElement>& layouts,
       const std::vector<unsigned int>&  indices);
  ~Mesh();

  void bind() const;
  void unBind() const;

  void draw(const TransformComponent&      transform,
            const std::shared_ptr<Shader>& shader, Entity entity);

  int getCount() const;

  void addTexture(TextureType type, const std::shared_ptr<Texture>& texture);

  std::unordered_map<TextureType, std::shared_ptr<Texture>>& getTextures();

  static std::shared_ptr<Mesh> Create(const std::vector<float>& vertices,
                                      const std::vector<BufferElement>& layouts,
                                      const std::vector<unsigned int>& indices);

  static std::shared_ptr<Mesh> Cube();

 private:
  std::shared_ptr<VertexArray>  _vao;
  std::shared_ptr<VertexBuffer> _vbo;
  std::shared_ptr<IndexBuffer>  _ebo;

  std::unordered_map<TextureType, std::shared_ptr<Texture>> _textures;
};

}  // namespace deft

#endif  // __DEFT_MESH_H__