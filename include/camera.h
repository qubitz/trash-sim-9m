#ifndef CAMERA_H
#define CAMERA_H

#include "graphics_headers.h"

class Camera
{
 public:
  Camera() {}
  ~Camera() {}
  bool Initialize(int w, int h);
  glm::mat4 GetProjection() { return projection; }
  glm::mat4 GetView() { return view; }
  void Update( glm::vec3 viewVect );

 private:
  glm::mat4 projection;
  glm::mat4 view;
};

#endif /* CAMERA_H */
