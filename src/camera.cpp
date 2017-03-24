#include "camera.h"

bool Camera::Initialize(int w, int h)
{
  view = glm::lookAt(glm::vec3(0.0, 25.0, -40.0),  // Eye Position
                     glm::vec3(0.0, 10.0, 0.0),     // Focus point
                     glm::vec3(0.0, 1.0, 1.0));    // Positive Y is up
  projection = glm::perspective(
      // FoV typically 90 degrees
      45.0f,
      // Aspect Ratio, so Circles stay Circular
      float(w) / float(h),
      // Distance to the near plane,
      //   normally a small value like this
      0.01f,
      // Distance to the far plane
      1000.0f);

  return true;
}

void Camera::Update(glm::vec3 viewVect)
{
  glm::vec3 eyePos, focusPos;

  eyePos   = glm::vec3(0.0, 25.0, -40.0);
  focusPos = glm::vec3(0.0, 10.0, 0.0);

  eyePos += viewVect;

  view = glm::lookAt(eyePos,                     // Eye Position
                     focusPos,                   // Focus point
                     glm::vec3(0.0, 1.0, 0.0));  // Positive Y is up
}
