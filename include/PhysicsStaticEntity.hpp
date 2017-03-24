#ifndef PHYSICSSTATIC_HPP_INCLUDED
#define PHYSICSSTATIC_HPP_INCLUDED

#include <btBulletDynamicsCommon.h>
#include "PhysicsEntity.hpp"
#include "PhysicsWorld.hpp"
#include "Types.hpp"

class PhysicsStaticEntity : public PhysicsEntity
{
 public:
  PhysicsStaticEntity();

  virtual void init(btVector3 position, btQuaternion rotation);
};

#endif
