#include "PhysicsStaticEntity.hpp"

PhysicsStaticEntity::PhysicsStaticEntity() : PhysicsEntity::PhysicsEntity() {}
void PhysicsStaticEntity::init(btVector3 position, btQuaternion rotation)
{
  m_mass           = 0;
  m_inertia        = btVector3(0, 0, 0);
  m_collisionShape = new btBvhTriangleMeshShape(m_triangleMesh, true);

  m_shapeMotionState =
      new btDefaultMotionState(btTransform(rotation, position));
  m_collisionShape->calculateLocalInertia(m_mass, m_inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(
      m_mass, m_shapeMotionState, m_collisionShape, m_inertia);
  shapeRigidBodyCI.m_restitution = 1;
  m_rigidBody                    = new btRigidBody(shapeRigidBodyCI);
}
