//
// Created by daniel on 10/31/16.
//

#include "PhysicsPlane.hpp"

PhysicsPlane::PhysicsPlane() : PhysicsEntity::PhysicsEntity() {}
void PhysicsPlane::init(btScalar mass, btVector3 inertia) {}
void PhysicsPlane::init(btVector3 normal, btScalar offset, btQuaternion rotation, btVector3 location)
{
  m_mass    = 0;
  m_inertia = btVector3(0, 0, 0);

  m_collisionShape   = new btStaticPlaneShape(normal, offset);
  m_shapeMotionState = new btDefaultMotionState(
      btTransform(rotation, location));
  m_collisionShape->calculateLocalInertia(m_mass, m_inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(
      m_mass, m_shapeMotionState, m_collisionShape, m_inertia);
  shapeRigidBodyCI.m_restitution = 0.2;

  m_rigidBody = new btRigidBody(shapeRigidBodyCI);
}
