#include "Entity.hpp"

Entity::Entity()
    : model_loaded(false)
    , m_trans_model()
    , m_scale_model()
    , m_vertices()
    , m_indices()
    , VB()
    , IB()
    , m_importer()
    , aTexture()
{
}

Entity::~Entity() { cleanup(); }
std::string Entity::get_ID() const { return m_entityID; }
void Entity::set_ID(std::string newID) { m_entityID = newID; }
void                            Entity::update()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++) std::cout << m_model[i][j] << ", ";
    std::cout << std::endl;
  }
}

void Entity::render()
{
  if (model_loaded)
  {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, VB);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, vertex));
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, uv));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                          (void*)offsetof(Vertex, normal));

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, aTexture);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);

    glDrawElements(GL_TRIANGLES, m_indices.size(), GL_UNSIGNED_INT, 0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
  }
}

glm::mat4 Entity::get_model() { return m_model; }
bool Entity::load_model(std::string modelFile, std::string textureFile)
{
  // Clear indicies and verticies in the event that the current model is
  //  being overridden
  m_vertices.clear();
  m_indices.clear();

  Vertex     inputVertex;
  aiMesh*    tempMesh;
  aiVector3D tempVertex;
  aiFace     tempFaces;
  aiVector3D tempTextCoors;
  aiVector3D tempNormal;

  unsigned int tempIndex;

  m_scene = m_importer.ReadFile(modelFile.c_str(),
                                aiProcess_Triangulate | aiProcess_FlipUVs);

  // Load Assimp model
  if (m_scene == NULL || m_scene->mRootNode == NULL)
  {
    // Oh! Here's our fun print function! :)
    print("Assimp failed to load model", modelFile,
          m_importer.GetErrorString());
    return false;
  }

  // Cycle through all aiMeshes
  for (unsigned int meshIndex = 0; meshIndex < m_scene->mNumMeshes; meshIndex++)
  {
    tempMesh = m_scene->mMeshes[meshIndex];

    // Cycle through all faces in mesh
    for (unsigned int faceIndex = 0; faceIndex < tempMesh->mNumFaces;
         faceIndex++)
    {
      tempFaces = tempMesh->mFaces[faceIndex];

      // Cycle through all indicies in face
      for (unsigned int indexIndex = 0; indexIndex < tempFaces.mNumIndices;
           indexIndex++)
      {
        // assign indiviual index within face to Indices
        tempIndex  = tempFaces.mIndices[indexIndex];
        tempVertex = tempMesh->mVertices[tempIndex];
        tempNormal = tempMesh->mNormals[tempIndex];

        if (tempMesh->HasTextureCoords(meshIndex))
        {
          // debug.log("The temp mesh has text coords");
          tempTextCoors = tempMesh->mTextureCoords[0][tempIndex];
        }
        else
        {
          tempTextCoors.x = 0;
          tempTextCoors.y = 0;
        }

        inputVertex =
            Vertex(glm::vec3(tempVertex.x, tempVertex.y, tempVertex.z),
                   glm::vec2(tempTextCoors.x, 1 - tempTextCoors.y),
                   glm::vec3(tempNormal.x, tempNormal.y, tempNormal.z));

        m_vertices.push_back(inputVertex);
        m_indices.push_back(tempIndex);
      }
    }
  }

  bind_model_to_gl(textureFile);
  model_loaded = true;

  delete tempMesh;
  tempMesh = NULL;

  // REFER TO COMMENTS IN cleanup
  // CALLING FREESCENE FUNCTION THROWS A DOUBLE FREE OR CORRUPTION ERROR
  // m_importer.FreeScene();
  return true;
}

void Entity::bind_model_to_gl(std::string textureFile)
{
  image.read(textureFile.c_str());
  int          imageWidth = image.columns(), imageHeight = image.rows();
  Magick::Blob imageData;
  image.write(&imageData, "RGBA");

  glGenTextures(1, &aTexture);

  glBindTexture(GL_TEXTURE_2D, aTexture);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, imageWidth, imageHeight, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, imageData.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  gluBuild2DMipmaps(GL_TEXTURE_2D, 4, image.columns(), image.rows(), GL_RGBA,
                    GL_UNSIGNED_BYTE, imageData.data());

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

  glGenBuffers(1, &VB);
  glBindBuffer(GL_ARRAY_BUFFER, VB);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * m_vertices.size(),
               &m_vertices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &IB);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_indices.size(),
               &m_indices[0], GL_STATIC_DRAW);
}

void Entity::cleanup()
{
  // print("Start cleanup");
  m_vertices.clear();
  m_indices.clear();

  // TODO: HOW DO WE PREVENT THE AISCENE FROM CAUSING A SEG FAULT UPON
  // ENTITY DESTRUCTION? THIS IS CURRENTLY THE ONLY WAY I CAN FIGURE THIS OUT.
  // BUT THIS IS CREATING A BAD BAD MEMORY LEAK.
  // WE CANNOT DELETE THE SCENE MANUALLY BECAUSE ASSIMP DOESN'T ALLOW US TO CALL
  // THE DESTRUCTOR OF AISCENE MANUALLY :( WTF ASSIMP
  // ATTEMPTING TO CALL m_importer.FreeScene() ALSO SEG FAULTS
  // IMPORTER SUPPOSIDLY DEALLOCATES AISCENE UPON DESTRUCTION, BUT THE
  // DESTRUCTION
  // OF THE IMPORTER IS SEG FAULTING, PROBABLY WHEN ATTEMPTING TO DESTROY ITS
  // CONTAINED AISCENE
  const aiScene* tempScene = m_importer.GetOrphanedScene();

  // THIS FUNCTION SUPPOSIDLY DEALLOCATES THE MEMORY FOR AISCENE, BUT CALLING
  // THIS
  // FUNCTION INSTEAD OF m_importer.GetOrphanedScene() CAUSES A SEG FAULT
  // ATTEMPTING TO DO SO IN THE SCOPE OF load_model ALSO SEG FAULTS
  // m_importer.FreeScene();

  // WE CANNOT DELETE THE AISCENE MANUALLY
  // delete tempScene;

  // print("End cleanup");
}

glm::mat4 Entity::get_trans_model() { return m_trans_model; }
glm::mat4 Entity::get_scale_model() { return m_scale_model; }
Entity& Entity::operator=(const Entity& other)
{
  // // Entity gets other's name
  // m_entityID = other.m_entityID;
  //
  // // Clear this entity's properties
  // m_properties.clear();
  //
  // // And clone the other's properties
  // m_properties.clone(other.m_properties);
  //
  // model_loaded = false;
  return *this;
}
