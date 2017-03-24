#include "graphics.h"
#include "PhysicsCube.hpp"
#include "PhysicsPlane.hpp"

Graphics::Graphics() {}
Graphics::~Graphics()
{
  delete can;
  can = NULL;
  
  for (PhysicsEntity* entity : m_physicsEntities)
  {
    if( entity != NULL )
    {
      delete entity;
      entity = NULL;
    }
  }
  
  for(PhysicsSphere * ball : m_balls)
  {
    if( ball != NULL )
    {
      delete ball;
      ball = NULL;
    }
  }
  
  for (Entity* entity : m_Entities)
  {
    if( entity != NULL )
    {
      delete entity;
      entity = NULL;
    }
  }
  
  for (PhysicsPlane* wall : m_walls)
  {
    if( wall != NULL )
    {
      delete wall;
      wall = NULL;
    }
  }
}

bool Graphics::Initialize(int width, int height)
{
// Used for the linux OS
#if !defined(__APPLE__) && !defined(MACOSX)
  // cout << glewGetString(GLEW_VERSION) << endl;
  glewExperimental = GL_TRUE;

  auto status = glewInit();

  // This is here to grab the error that comes from glew init.
  // This error is an GL_INVALID_ENUM that has no effects on the performance
  glGetError();

  // Check for error
  if (status != GLEW_OK)
  {
    std::cerr << "GLEW Error: " << glewGetErrorString(status) << "\n";
    return false;
  }
#endif

  // For OpenGL 3
  GLuint vao;
  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  // Init Camera
  m_camera = new Camera();
  if (!m_camera->Initialize(width, height))
  {
    printf("Camera Failed to Initialize\n");
    return false;
  }

  // Create the object
  m_physicsWorld = new PhysicsWorld();
  m_physicsWorld->init();

  ground = new PhysicsPlane();
  ground->Entity::load_model("models/blankPlane.obj", "../textures/floor.jpg");
  ground->init (btVector3 (0, 1, 0), 0, (btQuaternion (0, 0, 0, 1)), (btVector3 (0, 0, 0)));
  m_physicsWorld->add_to_world(ground);
  m_walls.push_back(ground);

  wall = new PhysicsPlane();
  wall->Entity::load_model("models/blankPlane.obj", "../textures/Silver.png");
  wall->init (btVector3 (1, 0, 0), 0, (btQuaternion (90, 90, 0, 0)), (btVector3 (150, 0, 0)));
  m_physicsWorld->add_to_world(wall);
  m_walls.push_back(wall);

  wall = new PhysicsPlane();
  wall->Entity::load_model("models/blankPlane.obj", "../textures/donald.jpg");
  wall->init (btVector3 (-1, 0, 0), 0, (btQuaternion (-90, 90, 0, 0)), (btVector3 (-150, 0, 0)));
  m_physicsWorld->add_to_world(wall);
  m_walls.push_back(wall);

  wall = new PhysicsPlane();
  wall->Entity::load_model("models/blankPlane.obj", "../textures/trashCan.png");
  wall->init (btVector3 (0, -1, 0), 0, (btQuaternion (0, 0, 0, 1)), (btVector3 (0, 150, 0)));
  m_physicsWorld->add_to_world(wall);
  m_walls.push_back(wall);

  can = new PhysicsStaticEntity();
  can->load_model("models/TrashCan1.obj", "../textures/trashCan.png");
  can->init(btVector3(.5, 0, 0), btQuaternion(0, 0, 0, 1));
  m_physicsWorld->add_to_world(can);

  officeStuff = new PhysicsStaticEntity();
  officeStuff->load_model("models/cubicle_section.obj", "../textures/cubicle.png");
  officeStuff->init(btVector3(-60, 0, 5), btQuaternion(0, 0, 0, 1));
  m_physicsWorld->add_to_world(officeStuff);
  m_physicsEntities.push_back(officeStuff);

  officeStuff = new PhysicsStaticEntity();
  officeStuff->load_model("models/cubicle_section.obj", "../textures/cubicle.png");
  officeStuff->init(btVector3(53, 0, 5), btQuaternion(0, 0, 0, 1));
  m_physicsWorld->add_to_world(officeStuff);
  m_physicsEntities.push_back(officeStuff);

  spawnX = 0;
  spawnY = 15;
  spawnZ = -30;

  PhysicsSphere * theFirstSphere = new PhysicsSphere();
  theFirstSphere->load_model("models/menu.obj", "../textures/Menu.png");
  theFirstSphere->init(10.0, btVector3(1, 1, 1), 1, btVector3(spawnX, spawnY, spawnZ));
  m_physicsWorld->add_to_world(theFirstSphere);
  m_balls.push_back(theFirstSphere);
  theFirstSphere = NULL;

  PhysicsStaticEntity * aVendingMachine = new PhysicsStaticEntity();
  aVendingMachine->load_model("models/vendingMachine.obj", "../textures/vending-machine.jpg");
  aVendingMachine->init(btVector3(-30, 0, 100), btQuaternion(0, 0, 0, 1));
  m_physicsWorld->add_to_world(aVendingMachine);
  m_physicsEntities.push_back(aVendingMachine);

  PhysicsStaticEntity * office = new PhysicsStaticEntity();
  office->load_model("models/managersOffice.obj", "../textures/cubicle.png");
  office->init(btVector3(0, 0, 100), btQuaternion(0, 0, 0, 1));
  m_physicsWorld->add_to_world(office);
  m_physicsEntities.push_back(office);

  giraffe = new PhysicsStaticEntity();
  giraffe->load_model("models/Graf.obj", "../textures/giraffeColor.png");
  giraffe->init(btVector3(5, 13, 60), btQuaternion(0, 1, 0, 1));
  m_physicsWorld->add_to_world(giraffe);
  m_physicsEntities.push_back(giraffe);

  fan = new PhysicsStaticEntity();
  fan->load_model("models/fan.obj", "../textures/fan.png");
  fan->init(btVector3(17, 0, 20), btQuaternion(0, 0, 0, 1));
  m_physicsWorld->add_to_world(fan);
  m_physicsEntities.push_back(fan);

  m_lightPositionVector = glm::vec4(0.0, 10.0, 60.0, 1.0);
  m_currentShader       = 0;

  // Set up the shaders
  m_shader = new Shader();
  if (!m_shader->Initialize())
  {
    printf("Shader Failed to Initialize\n");
    return false;
  }

  // Add the vertex shader
  if (!m_shader->AddShader(GL_VERTEX_SHADER))
  {
    printf("Vertex Shader failed to Initialize\n");
    return false;
  }

  // Add the fragment shader
  if (!m_shader->AddShader(GL_FRAGMENT_SHADER))
  {
    printf("Fragment Shader failed to Initialize\n");
    return false;
  }

  // Connect the program
  if (!m_shader->Finalize())
  {
    printf("Program to Finalize\n");
    return false;
  }

  m_controlSwitch = m_shader->GetUniformLocation("controlSwitch");
  if (m_controlSwitch == INVALID_UNIFORM_LOCATION)
  {
    printf("m_controlSwitch not found\n");
    return false;
  }

  // Locate the projection matrix in the shader
  m_projectionMatrix = m_shader->GetUniformLocation("projectionMatrix");
  if (m_projectionMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_projectionMatrix not found\n");
    return false;
  }

  // Locate the view matrix in the shader
  m_viewMatrix = m_shader->GetUniformLocation("viewMatrix");
  if (m_viewMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_viewMatrix not found\n");
    return false;
  }

  // Locate the model matrix in the shader
  m_modelMatrix = m_shader->GetUniformLocation("modelMatrix");
  if (m_modelMatrix == INVALID_UNIFORM_LOCATION)
  {
    printf("m_modelMatrix not found\n");
    return false;
  }

  m_lightPosition = m_shader->GetUniformLocation("LightPosition");
  if (m_lightPosition == INVALID_UNIFORM_LOCATION)
  {
    printf("m_lightPosition not found\n");
    return false;
  }

  m_ambientProduct = m_shader->GetUniformLocation("AmbientProduct");
  if (m_ambientProduct == INVALID_UNIFORM_LOCATION)
  {
    printf("m_ambientProduct not found\n");
    return false;
  }

  m_diffuseProduct = m_shader->GetUniformLocation("DiffuseProduct");
  if (m_diffuseProduct == INVALID_UNIFORM_LOCATION)
  {
    printf("m_diffuseProduct not found\n");
    return false;
  }

  m_specularProduct = m_shader->GetUniformLocation("SpecularProduct");
  if (m_specularProduct == INVALID_UNIFORM_LOCATION)
  {
    printf("m_diffuseProduct not found\n");
    return false;
  }

  m_shininess = m_shader->GetUniformLocation("Shininess");
  if (m_shininess == INVALID_UNIFORM_LOCATION)
  {
    printf("m_shininess not found\n");
    return false;
  }

  ballTimer = 0;
  ballInAir = false;
  cheatMode = false;
  streak = 0;
  highscore = 0;

  // enable depth testing
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  return true;
}

void Graphics::Update(float dt, glm::vec3 viewVect)
{
  //ballTimer += dt;
  m_physicsWorld->dynamicsWorld->stepSimulation(dt /500.f, 10);

 // ground->update(dt);
  can->update(dt);

  m_camera->Update(viewVect);
  
  for(PhysicsEntity * entity : m_physicsEntities)
  {
    entity->update (dt);
  }

  for(PhysicsPlane * walls : m_walls)
  {
    walls->update (dt);
  }

  for(PhysicsSphere * ball : m_balls)
  {
    ball->update(dt);
  }

  // Check if we need to spawn in a new ball
  glm::vec3 positionOfActiveBall = get_position_of_active_ball();
  glm::vec3 positionOfFan = get_position_of_fan();

  if(std::abs(positionOfFan.z - positionOfActiveBall.z) <= 5)
  {
    launch_ball(btVector3(-0.001, 0, 0), true);
  }

  if(positionOfActiveBall.y <= 2.0f)
  {
    glm::vec3 positionOfCan = get_position_of_can();
    
    
    if(std::abs(positionOfCan.z - positionOfActiveBall.z) <= 2 and 
       std::abs(positionOfCan.x - positionOfActiveBall.x) <= 2)
    {
      streak += 1;
      glm::vec3 canPos = get_position_of_can();
      set_can_pos(canPos.x, canPos.y, canPos.z + 3);
    }
    else
    {
      // To optimize, only move the can back if the user had some sort of streak going
      
          
      streak = 0;
    }

    if(streak > highscore)
      highscore = streak;

    //print("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
    print("Current streak:", streak);
    print("Current highscore:", highscore);

    spawn_new_ball();
  }

}

void Graphics::Render()
{
  // clear the screen
  glClearColor(0.0, 0.0, 0.0, 1.0);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Start the correct program
  m_shader->Enable();

  glUniform1i(m_controlSwitch, m_currentShader);
  glUniform4fv(m_lightPosition, 1, glm::value_ptr(m_lightPositionVector));
  glUniform4fv(m_ambientProduct, 1, glm::value_ptr(m_ambientProductVector));
  glUniform4fv(m_diffuseProduct, 1,
               glm::value_ptr(glm::vec4(1.0, 1.0, 1.0, 1.0)));
  glUniform4fv(m_specularProduct, 1, glm::value_ptr(m_specularProductVector));
  glUniform1f(m_shininess, GLfloat(0.5f));

  // Send in the projection and view to the shader
  glUniformMatrix4fv(m_projectionMatrix, 1, GL_FALSE,
                     glm::value_ptr(m_camera->GetProjection()));
  glUniformMatrix4fv(m_viewMatrix, 1, GL_FALSE,
                     glm::value_ptr(m_camera->GetView()));


  glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE,
                       glm::value_ptr(can->get_model()));
    can->render();
  for (PhysicsEntity* entity : m_physicsEntities)
  {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE,
                       glm::value_ptr(entity->get_model()));
    entity->render();
  }

  for(PhysicsSphere * ball : m_balls)
  {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE,
                       glm::value_ptr(ball->get_model()));
    ball->render();
  }

  for (Entity* entity : m_Entities)
  {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE,
                       glm::value_ptr(entity->get_model()));
    entity->render();
  }

  for (PhysicsPlane* wall : m_walls)
  {
    glUniformMatrix4fv(m_modelMatrix, 1, GL_FALSE,
                       glm::value_ptr(wall->get_model()));
    wall->render();
  }

  //Get any errors from OpenGL
  auto error = glGetError();
  if (error != GL_NO_ERROR)
  {
    std::string val = ErrorString(error);
    //DEBUG("Error initializing OpenGL! " << error << ", " << val);  
  }

}

std::string Graphics::ErrorString(GLenum error)
{
  if (error == GL_INVALID_ENUM)
  {
    return "GL_INVALID_ENUM: An unacceptable value is specified for an "
           "enumerated argument.";
  }

  else if (error == GL_INVALID_VALUE)
  {
    return "GL_INVALID_VALUE: A numeric argument is out of range.";
  }

  else if (error == GL_INVALID_OPERATION)
  {
    return "GL_INVALID_OPERATION: The specified operation is not allowed in "
           "the current state.";
  }

  else if (error == GL_INVALID_FRAMEBUFFER_OPERATION)
  {
    return "GL_INVALID_FRAMEBUFFER_OPERATION: The framebuffer object is not "
           "complete.";
  }

  else if (error == GL_OUT_OF_MEMORY)
  {
    return "GL_OUT_OF_MEMORY: There is not enough memory left to execute the "
           "command.";
  }
  else
  {
    return "None";
  }
}

void Graphics::moveLight(glm::vec4 movementVec)
{
  m_lightPositionVector += movementVec;
}

void Graphics::adjustAmbientProduct(glm::vec4 adjustAmount)
{
  m_ambientProductVector += adjustAmount;
}

void Graphics::adjustSpecularProduct(glm::vec4 adjustAmount)
{
  m_specularProductVector += adjustAmount;
}

void Graphics::switchLightingShader() { m_currentShader = 1 - m_currentShader; }

void Graphics::launch_ball(btVector3 force, bool override) 
{ 
  if(not ballInAir || cheatMode || override){
    // Get active ball
    PhysicsSphere * ballToLaunch = m_balls.back();

    // Unlock and launch the fucker
    ballToLaunch->unlock();
    ballToLaunch->launch(force); 

    ballInAir = true;
  }

}

glm::vec3 Graphics::get_position_of_active_ball()
{
  glm::mat4 model = m_balls.back()->get_model();

  return glm::vec3(model[3]);
}

glm::vec3 Graphics::get_position_of_can()
{
  glm::mat4 model = can->get_model();

  return glm::vec3(model[3]);
}

glm::vec3 Graphics::get_position_of_fan()
{
  glm::mat4 model = fan->get_model();

  return glm::vec3(model[3]);
}

void Graphics::reset_ball()
{
  // Only allow a reset if the ball has at least been released from the player
  if(ballInAir)
    spawn_new_ball();
}

void Graphics::spawn_new_ball()
{
  PhysicsSphere * newBall = new PhysicsSphere();
  newBall->load_model("models/Paper.obj", "../textures/donald.jpg");
  newBall->init(0.05, btVector3(1, 1, 1), 1, btVector3(spawnX, spawnY, spawnZ), btQuaternion(rand(), rand(), rand(), 1));
  m_physicsWorld->add_to_world(newBall);
  m_balls.push_back(newBall);
  newBall = NULL;

  ballInAir = false;



  // Delete a ball if we have too many
  if(menu || m_balls.size() > 5)
  {
    // Get reference to ball in front of list
    PhysicsSphere * ballToDelete = m_balls.front();

    // Remove it from the list
    m_balls.erase(m_balls.begin());

    //removeFrom
    m_physicsWorld->remove_from_world(ballToDelete);

    // Deallocate the memory
    delete ballToDelete;

    ballToDelete = NULL;
    menu = false;
  }
}

void Graphics::enable_cheats()
{
  cheatMode = !cheatMode;
}

void Graphics::set_can_pos(float x, float y, float z)
{

  //glm::vec3 canPos = get_position_of_can();
  m_physicsWorld->remove_from_world(can);

  delete can;

  can = new PhysicsStaticEntity();
  can->load_model("models/TrashCan1.obj", "../textures/trashCan.png");
  can->init(btVector3(x, y, z), btQuaternion(0, 0, 0, 1));
  m_physicsWorld->add_to_world(can);
}
