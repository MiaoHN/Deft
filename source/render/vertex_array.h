#ifndef __DEFT_VERTEX_ARRAY_H__
#define __DEFT_VERTEX_ARRAY_H__

namespace deft {

class VertexArray {
 public:
  VertexArray();
  ~VertexArray();

  void bind() const;
  void unBind() const;

 private:
  unsigned int _id;
};

}  // namespace deft

#endif  // __DEFT_VERTEX_ARRAY_H__