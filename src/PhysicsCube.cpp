//
// Created by daniel on 10/31/16.
//

#include "PhysicsCube.hpp"

PhysicsCube::PhysicsCube() : PhysicsEntity::PhysicsEntity(), m_rotated(false) {}
PhysicsCube::~PhysicsCube() {}
void PhysicsCube::init(btScalar mass, btVector3 inertia, btVector3 position)
{
  m_mass    = mass;
  m_inertia = inertia;

  m_collisionShape = new btBoxShape(btVector3(1, 1, 1));
  m_shapeMotionState =
      new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), position));
  m_collisionShape->calculateLocalInertia(m_mass, m_inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(
      m_mass, m_shapeMotionState, m_collisionShape, m_inertia);
  shapeRigidBodyCI.m_restitution = 1;

  m_rigidBody = new btRigidBody(shapeRigidBodyCI);
}

void PhysicsCube::update(float dt, bool rotate, bool launch)
{
  btTransform trans;
  btVector3   torqueVec;

  m_rigidBody->activate(true);

  PhysicsEntity::update(dt);
}

void PhysicsCube::setGameType(int type) { m_gameType = type; }
