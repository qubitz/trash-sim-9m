#include "PhysicsSphere.hpp"

PhysicsSphere::PhysicsSphere() : PhysicsEntity() {}
void PhysicsSphere::init(btScalar mass, btVector3 inertia, btScalar radius,
                         btVector3 position, btQuaternion rotation)
{
  m_mass    = mass;
  m_inertia = inertia;

  m_collisionShape = new btSphereShape(radius);
  m_shapeMotionState =
      new btDefaultMotionState(btTransform(rotation, position));
  m_collisionShape->calculateLocalInertia(m_mass, m_inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(
      m_mass, m_shapeMotionState, m_collisionShape, m_inertia);
  shapeRigidBodyCI.m_restitution = 0.01;

  m_rigidBody = new btRigidBody(shapeRigidBodyCI);

  m_rigidBody->activate(false);
  m_rigidBody->setLinearFactor(btVector3(0.f, 0.f, 0.f));
}

void PhysicsSphere::update(float dt)
{
  PhysicsEntity::update(dt);
}

void PhysicsSphere::launch(btVector3 force)
{
  //glm::vec3 position = glm::vec3(m_model[3]);
  //m_rigidBody->setLinearFactor(btVector3(1.f, 1.f, 1.f));
    m_rigidBody->activate();
    m_rigidBody->applyCentralImpulse(force);
}

void PhysicsSphere::unlock()
{
  glm::vec3 position = glm::vec3(m_model[3]);
  //print(position.x, position.y, position.z);
  m_rigidBody->setLinearFactor(btVector3(1.f, 1.f, 1.f));
  //print(position.x, position.y, position.z);
}