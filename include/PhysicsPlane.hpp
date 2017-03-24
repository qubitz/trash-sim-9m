//
// Created by daniel on 10/31/16.
//

#ifndef PA8_PHYSICSPLANE_H
#define PA8_PHYSICSPLANE_H

#include "PhysicsEntity.hpp"

class PhysicsPlane : public PhysicsEntity
{
 public:
  PhysicsPlane();

  virtual void init(btScalar mass, btVector3 inertia);
  virtual void init(btVector3 normal, btScalar offset, btQuaternion rotation = btQuaternion(0, 0, 0, 1), btVector3 location = btVector3(0, 0, 0));
};

#endif  // PA8_PHYSICSPLANE_H
