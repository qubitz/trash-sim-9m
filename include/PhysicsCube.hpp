//
// Created by daniel on 10/31/16.
//

#ifndef PA8_PHYSICSCUBE_H
#define PA8_PHYSICSCUBE_H

#include <btBulletDynamicsCommon.h>
#include "PhysicsEntity.hpp"
#include "PhysicsWorld.hpp"
#include "Types.hpp"

class PhysicsCube : public PhysicsEntity
{
 public:
  PhysicsCube();

  virtual ~PhysicsCube();

  virtual void init(btScalar mass, btVector3 inertia, btVector3 position);

  virtual void update(float dt, bool rotate, bool launch);

  void setGameType(int type);

 private:
  bool m_rotated;
  int  m_gameType;
};

#endif  // PA8_PHYSICSCUBE_H
