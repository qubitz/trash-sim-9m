#ifndef PHYSICSENTITY_HPP_INCLUDED
#define PHYSICSENTITY_HPP_INCLUDED

#include <btBulletDynamicsCommon.h>
#include "Entity.hpp"
#include "PhysicsWorld.hpp"
#include "Types.hpp"

class PhysicsEntity : public Entity
{
 public:
  PhysicsEntity();

  virtual ~PhysicsEntity();

  virtual void update(float dt);

  virtual bool load_model(std::string modelFile, std::string textureFile);

  virtual void init(btScalar mass, btVector3 inertia, btVector3 position);

  void cleanup();

 protected:
  btScalar          m_mass;
  btVector3         m_inertia;
  btCollisionShape* m_collisionShape;
  btTriangleMesh*   m_triangleMesh;
  btRigidBody*      m_rigidBody;

  btDefaultMotionState* m_shapeMotionState;

  friend PhysicsWorld;
};

#endif
