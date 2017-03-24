#ifndef PHYSICSSPHERE_HPP_INCLUDED
#define PHYSICSSPHERE_HPP_INCLUDED

#include "PhysicsEntity.hpp"

class PhysicsSphere : public PhysicsEntity
{
 public:
  PhysicsSphere();

  void init(btScalar mass, btVector3 inertia, btScalar radius,
            btVector3 position, btQuaternion = btQuaternion(0, 0, 0, 1));

  virtual void update(float dt);

  void launch(btVector3 force);

  void unlock();
};

#endif
