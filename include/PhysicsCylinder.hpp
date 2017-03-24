#ifndef PHYSICSCYLINDER_HPP_INCLUDED
#define PHYSICSCYLINDER_HPP_INCLUDED

#include "PhysicsEntity.hpp"

class PhysicsCylinder : public PhysicsEntity
{
 public:
  PhysicsCylinder();

  void init(btScalar mass, btVector3 inertia, btVector3 position);
};

#endif
