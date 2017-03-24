#ifndef GRAPHICS_H
#define GRAPHICS_H

#include <SDL2/SDL.h>
#include <btBulletDynamicsCommon.h>
#include <iostream>
#include <random>
#include <cstdlib>

#include "Entity.hpp"
#include "GFKUtil.hpp"
#include "PhysicsStaticEntity.hpp"
#include "PhysicsCube.hpp"
#include "PhysicsEntity.hpp"
#include "PhysicsPlane.hpp"
#include "PhysicsWorld.hpp"
#include "PhysicsCylinder.hpp"
#include "PhysicsSphere.hpp"
#include "camera.h"
#include "graphics_headers.h"
#include "shader.h"

class Graphics
{
 public:
  Graphics();
  ~Graphics();
  bool Initialize(int width, int height);
  void Update(float dt, glm::vec3 viewVect);
  void Render();

  void moveLight(glm::vec4 movementVec);
  void adjustAmbientProduct(glm::vec4 adjustAmount);
  void adjustSpecularProduct(glm::vec4 adjustAmount);
  void switchLightingShader();
  void launch_ball(btVector3, bool);
  void reset_ball();
  void enable_cheats();
  void set_can_pos(float x, float y, float z);

 private:
  std::string ErrorString(GLenum error);
  glm::vec3 get_position_of_active_ball();
  glm::vec3 get_position_of_can();
  glm::vec3 get_position_of_fan();
  void spawn_new_ball();

  Camera *m_camera;
  Shader *m_shader;

  GLint m_projectionMatrix;
  GLint m_viewMatrix;
  GLint m_modelMatrix;
  GLint m_lightPosition;
  GLint m_ambientProduct;
  GLint m_diffuseProduct;
  GLint m_specularProduct;
  GLint m_shininess;
  GLint m_controlSwitch;

  glm::vec4 m_lightPositionVector;
  glm::vec4 m_ambientProductVector;
  glm::vec4 m_specularProductVector;

  int m_currentShader;
  int ballTimer;
  int spawnX, spawnY, spawnZ;
  bool ballInAir;
  bool cheatMode;
  bool menu;
  int streak;
  int highscore;

  PhysicsWorld *        m_physicsWorld;
  PhysicsStaticEntity * can;
  PhysicsStaticEntity * officeStuff;
  PhysicsSphere *       trash;
  PhysicsPlane *        ground;
  PhysicsPlane *        wall;
  PhysicsStaticEntity *       giraffe;
  PhysicsStaticEntity * fan;


  std::vector<PhysicsEntity *> m_physicsEntities;
  std::vector<Entity *> m_Entities;

  std::vector<PhysicsPlane *>  m_walls;

  std::list<PhysicsSphere *> m_balls;
};

#endif /* GRAPHICS_H */
