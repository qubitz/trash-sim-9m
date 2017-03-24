#include "engine.h"

Engine::Engine(string name, int width, int height)
{
  m_WINDOW_NAME      = name;
  m_WINDOW_WIDTH     = width;
  m_WINDOW_HEIGHT    = height;
  m_FULLSCREEN       = false;
}

Engine::Engine(string name)
{
  m_WINDOW_NAME   = name;
  m_WINDOW_HEIGHT = 0;
  m_WINDOW_WIDTH  = 0;
  m_FULLSCREEN    = true;
}

Engine::~Engine()
{
  delete m_window;
  delete m_graphics;
  m_window   = NULL;
  m_graphics = NULL;
}

bool Engine::Initialize()
{
  // Start a window
  m_window = new Window();
  if (!m_window->Initialize(m_WINDOW_NAME, &m_WINDOW_WIDTH, &m_WINDOW_HEIGHT))
  {
    printf("The window failed to initialize.\n");
    return false;
  }

  // Start the graphics
  m_graphics = new Graphics();
  if (!m_graphics->Initialize(m_WINDOW_WIDTH, m_WINDOW_HEIGHT))
  {
    printf("The graphics failed to initialize.\n");
    return false;
  }

  // Set the time
  m_currentTimeMillis = GetCurrentTimeMillis();

  mouseXWhenReleased = mouseYWhenReleased = mouseXWhenClicked = mouseYWhenClicked = -1;

  // No errors
  return true;
}

void Engine::Run()
{
  m_running   = true;

  while (m_running)
  {
    // Update the DT
    m_DT = getDT();

    // Check the keyboard and mouse input
    while (SDL_PollEvent(&m_event) != 0)
    {
      if (m_event.type == SDL_QUIT)
      {
        // Exit program
        m_running = false;
      }
      else
      {
        // Read keyboard and mouse input
        Keyboard();
        Mouse();
      }
    }

    m_graphics->Update(m_DT, m_viewVect);

    m_graphics->Render();

    // Swap to the Window
    m_window->Swap();
  }
}

void Engine::Keyboard()
{
  if (m_event.type == SDL_KEYDOWN)
  {
    switch (m_event.key.keysym.sym)
    {
      // General controls
      case SDLK_ESCAPE:
        print("Exiting program");
        m_running = false;
        break;
      case SDLK_p:
        if (m_pause)
          print("Resuming Game");
        else
          print("Pausing game");
        m_pause = !m_pause;
        break;

      case SDLK_r:
        //Force reset
        m_graphics->reset_ball();
        break;

      case SDLK_BACKSLASH:
        m_graphics->enable_cheats();

      // Light controls c:
      case SDLK_LEFT:
        m_graphics->moveLight(glm::vec4(1.0, 0, 0, 0));
        break;
      case SDLK_RIGHT:
        m_graphics->moveLight(glm::vec4(-1.0, 0, 0, 0));
        break;
      case SDLK_UP:
        m_graphics->moveLight(glm::vec4(0, 0, 1, 0));
        break;
      case SDLK_DOWN:
        m_graphics->moveLight(glm::vec4(0, 0, -1, 0));
        break;
      case SDLK_a:
        m_graphics->adjustAmbientProduct(glm::vec4(-.1, -.1, -.1, -.1));
        break;
      case SDLK_s:
        m_graphics->adjustSpecularProduct(glm::vec4(-.1, -.1, -.1, -.1));
        break;
      case SDLK_q:
        m_graphics->adjustAmbientProduct(glm::vec4(.1, .1, .1, .1));
        break;
      case SDLK_w:
        m_graphics->adjustSpecularProduct(glm::vec4(.1, .1, .1, .1));
        break;
      case SDLK_v:
        m_graphics->switchLightingShader();
        break;
        
      // Camera controls
      case SDLK_i:
        m_viewVect += glm::vec3(0.0, 1.0, 0.0);
        break;
      case SDLK_j:
        m_viewVect += glm::vec3(1.0, 0.0, 0.0);
        break;
      case SDLK_k:
        m_viewVect += glm::vec3(0.0, -1.0, 0.0);
        break;
      case SDLK_l:
        m_viewVect += glm::vec3(-1.0, 0.0, 0.0);
        break;
    }
  }
  else if (m_event.type == SDL_KEYUP)
  {
    switch (m_event.key.keysym.sym)
    {
      default:
        break;
    }
  }
}

void Engine::Mouse() 
{
  int x, y;
  // if( SDL_GetMouseState(&x, &y) & SDL_BUTTON(SDL_BUTTON_LEFT) )
  // {
  //   mouseXWhenClicked = x;
  //   mouseYWhenClicked = y;
  // }

  if(m_event.type == SDL_MOUSEBUTTONDOWN)
  {
    SDL_GetMouseState(&x, &y);
    mouseXWhenClicked = x;
    mouseYWhenClicked = y;
    velocityTimer = SDL_GetTicks();
  }
  else if(m_event.type == SDL_MOUSEBUTTONUP)
  {
    SDL_GetMouseState(&x, &y);
    mouseXWhenReleased = x;
    mouseYWhenReleased = y;

    launch_ball(create_mouse_force_vec());
  }

}

btVector3 Engine::create_mouse_force_vec()
{
  btVector3 vecToReturn(0, 0, 1);

  vecToReturn.setX(-(mouseXWhenReleased - mouseXWhenClicked));
  vecToReturn.setY(-(mouseYWhenReleased - mouseYWhenClicked));

  mouseXWhenReleased = mouseYWhenReleased = mouseXWhenClicked = mouseYWhenClicked = -1;

  //vecToReturn.normalize();

  vecToReturn.setZ(vecToReturn.getY());

  int speed = SDL_GetTicks() - velocityTimer;

  return vecToReturn * 125.0f/(float)speed * 1.f / 500.f;
}

void Engine::launch_ball(btVector3 forceVec)
{
  m_graphics->launch_ball(forceVec, false);
}

unsigned int Engine::getDT()
{
  long long TimeNowMillis = GetCurrentTimeMillis();
  assert(TimeNowMillis >= m_currentTimeMillis);
  unsigned int DeltaTimeMillis =
      (unsigned int)(TimeNowMillis - m_currentTimeMillis);
  m_currentTimeMillis = TimeNowMillis;
  return DeltaTimeMillis;
}

long long Engine::GetCurrentTimeMillis()
{
  timeval t;
  gettimeofday(&t, NULL);
  long long ret = t.tv_sec * 1000 + t.tv_usec / 1000;
  return ret;
}

float Engine::get_dt_as_float()
{
//  Uint32 tempTime = SDL_GetTicks();
//
//  float dt = tempTime - lastFrameTickCount;
//
//  lastFrameTickCount = tempTime;
//
//  return dt / 1000.0f;
}
