#ifndef ENGINE_H
#define ENGINE_H

#include <assert.h>
#include <btBulletDynamicsCommon.h>
#include <sys/time.h>

#include "graphics.h"
#include "window.h"

class Engine
{
 public:
  Engine(string name, int width, int height);
  Engine(string name);
  ~Engine();
  bool         Initialize();
  void         Run();
  void         Keyboard();
  void         Mouse();
  unsigned int getDT();
  long long    GetCurrentTimeMillis();
  float        get_dt_as_float(); // New and improved DT!
  bool         Menu();

 private:

  btVector3 create_mouse_force_vec();
  void launch_ball(btVector3);

  // Window related variables
  Window*   m_window;
  string    m_WINDOW_NAME;
  int       m_WINDOW_WIDTH;
  int       m_WINDOW_HEIGHT;
  bool      m_FULLSCREEN;
  SDL_Event m_event;

  Graphics*    m_graphics;
  glm::vec3    m_viewVect;
  unsigned int m_DT;
  long long    m_currentTimeMillis;
  bool         m_running;
  bool         m_pause = false;
  int velocityTimer;

  int mouseXWhenClicked, mouseYWhenClicked;
  int mouseXWhenReleased, mouseYWhenReleased;

  //    bool m_up, m_down, m_left, m_right;
};

#endif  // ENGINE_H
