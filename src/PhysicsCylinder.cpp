#include "PhysicsCylinder.hpp"

PhysicsCylinder::PhysicsCylinder() : PhysicsEntity() {}
void PhysicsCylinder::init(btScalar mass, btVector3 inertia, btVector3 position)
{
  m_mass    = mass;
  m_inertia = inertia;

  m_collisionShape = new btCylinderShape(btVector3(2, 10, 10));
  m_shapeMotionState =
      new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), position));
  m_collisionShape->calculateLocalInertia(m_mass, m_inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(
      m_mass, m_shapeMotionState, m_collisionShape, m_inertia);
  shapeRigidBodyCI.m_restitution = 0.9;

  m_rigidBody = new btRigidBody(shapeRigidBodyCI);
}
