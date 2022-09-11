#ifndef __DEFT_MESH_H__
#define __DEFT_MESH_H__

#include <memory>
#include <vector>

#include "render/index_buffer.h"
#include "render/vertex_array.h"
#include "render/vertex_buffer.h"

namespace deft {

class Mesh {
 public:
  Mesh();
  Mesh(const std::vector<float>&         vertices,
       const std::vector<BufferElement>& layouts,
       const std::vector<unsigned int>&  indices);
  ~Mesh();

  void bind() const;
  void unBind() const;

  int getCount() const;

  static std::shared_ptr<Mesh> Create(const std::vector<float>& vertices,
                                      const std::vector<BufferElement>& layouts,
                                      const std::vector<unsigned int>& indices);

 private:
  std::shared_ptr<VertexArray>  _vao;
  std::shared_ptr<VertexBuffer> _vbo;
  std::shared_ptr<IndexBuffer>  _ebo;
};

}  // namespace deft

#endif  // __DEFT_MESH_H__