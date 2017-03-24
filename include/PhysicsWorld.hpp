#ifndef PHYSICSWORLD_HPP_INCLUDED
#define PHYSICSWORLD_HPP_INCLUDED

#include <btBulletDynamicsCommon.h>
#include "PhysicsEntity.hpp"
#include "Types.hpp"

class PhysicsWorld
{
 public:
  PhysicsWorld();

  ~PhysicsWorld();

  void init();

  void add_to_world(PhysicsEntity* theEntity);
  void remove_from_world(PhysicsEntity * theEntity);

  void cleanup();

 public:
  btBroadphaseInterface*               broadphase;
  btDefaultCollisionConfiguration*     collisionConfiguration;
  btCollisionDispatcher*               dispatcher;
  btSequentialImpulseConstraintSolver* solver;
  btDiscreteDynamicsWorld*             dynamicsWorld;

  bool cleanedUp;
};

#endif
