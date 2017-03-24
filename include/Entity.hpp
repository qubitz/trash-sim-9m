#ifndef GFK_ENTITY_INCLUDED
#define GFK_ENTITY_INCLUDED

#include <Magick++.h>
#include <SDL2/SDL.h>
#include <assimp/color4.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>
#include <assimp/Importer.hpp>
#include <string>
#include "GFKUtil.hpp"
#include "PropertyManager.hpp"
#include "Types.hpp"
#include "graphics_headers.h"

class Entity
{
 public:
  // This entity's property manager.
  // PropertyManager m_properties;

  /**
  * Default constructor for the entity class. Requires a string ID
  * to label this entity for lookup.
  */
  Entity();

  /**
  * Copy constructor. Performs a full copy. Other entity's name and properties
  * get assigned to this entity.
  */
  // Entity(const Entity& other);

  /**
  * Virtual Deconstructor definition for polymorphic instances.
  */
  virtual ~Entity();

  /**
  * Returns the string ID for this entity
  */
  std::string get_ID() const;

  virtual void set_ID(std::string newID);

  /**
  * Default update function for entity does nothing, but allows for
  * definition in the event parent and child instances of this class
  * are held in the same group.
  */
  virtual void update();

  /**
  * Default rendering of entity. Checks to see if the model has been loaded.
  * If so, then the model is rendered.
  */
  virtual void render();

  /**
  * Loads an .obj model file created in blender.
  */
  bool load_model(std::string modelFile, std::string textureFile);

  /**
  * Proper deallocation/smooth cleanup of this default entity.
  */
  virtual void cleanup();

  // TODO: Perhaps define a pure virtual cleanup for polymorphic classes?

  glm::mat4 get_trans_model();
  glm::mat4 get_scale_model();

  glm::mat4 get_model();

  /**
  * Overloaded assignment operator. Performs a full copy. Entity's properties
  * and name get reassigned to copy entity. Note that to render the entity
  * after copying, the load_model function first needs to be called.
  */
  Entity& operator=(const Entity&);

 protected:
  /**
  * When an object is loaded, this function tells openGL how to reference it.
  */
  void bind_model_to_gl(std::string textureFile);

 protected:
  /// The string ID referring to this entity and used to find this
  /// entity in the event it is in a group.
  std::string m_entityID;

  /// The 4x4 model matrix that doesn't identify with it's sex
  glm::mat4 m_trans_model;

  /// The 4x4 model matrix that is used for scaling
  glm::mat4 m_scale_model;

  glm::mat4 m_model;

  bool model_loaded;

  // TODO: Model loading should probably be handled by a seperate class!
  // Doing so reduces the bloat of each entity and is better design in
  // general for reasons I don't want to go into in the comment. :)
  // Will we ACTUALLY do that? I don't know.
  // Probably Not...
  std::vector<Vertex>       m_vertices;
  std::vector<unsigned int> m_indices;
  GLuint                    VB;
  GLuint                    IB;
  Assimp::Importer          m_importer;
  const aiScene*            m_scene;
  GLuint                    aTexture;
  Magick::Image             image;
};

#endif
