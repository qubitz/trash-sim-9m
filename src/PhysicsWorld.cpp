#include "PhysicsWorld.hpp"

PhysicsWorld::PhysicsWorld()
    : broadphase(NULL)
    , collisionConfiguration(NULL)
    , dispatcher(NULL)
    , solver(NULL)
    , dynamicsWorld(NULL)
    , cleanedUp(true)
{
}

PhysicsWorld::~PhysicsWorld() { cleanup(); }
void PhysicsWorld::init()
{
  if (cleanedUp)
  {
    // Assuming that all the pointers will be created correctly
    // But you know what they say about assuming...
    broadphase             = new btDbvtBroadphase();
    collisionConfiguration = new btDefaultCollisionConfiguration();
    dispatcher             = new btCollisionDispatcher(collisionConfiguration);
    solver                 = new btSequentialImpulseConstraintSolver();

    dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver,
                                                collisionConfiguration);

    dynamicsWorld->setGravity(btVector3(0, -9.81, 0));

    cleanedUp = false;
  }
}

void PhysicsWorld::add_to_world(PhysicsEntity* theEntity)
{
  dynamicsWorld->addRigidBody(theEntity->m_rigidBody);
}

void PhysicsWorld::remove_from_world(PhysicsEntity * theEntity)
{
  dynamicsWorld->removeRigidBody(theEntity->m_rigidBody);
}

void PhysicsWorld::cleanup()
{
  // Check if the physics world is already cleaned up because we
  // cannot delete pointers that don't exist
  if (not cleanedUp)
  {
    delete broadphase;
    delete collisionConfiguration;
    delete dispatcher;
    delete solver;
    delete dynamicsWorld;

    broadphase             = NULL;
    collisionConfiguration = NULL;
    dispatcher             = NULL;
    solver                 = NULL;
    dynamicsWorld          = NULL;

    cleanedUp = true;
  }
}
