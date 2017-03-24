#include "PhysicsEntity.hpp"

PhysicsEntity::PhysicsEntity()
    : Entity::Entity(), m_triangleMesh(NULL), m_rigidBody(NULL)
{
}

PhysicsEntity::~PhysicsEntity()
{
  delete m_collisionShape;
  delete m_triangleMesh;
  delete m_rigidBody;
  delete m_shapeMotionState;
}

void PhysicsEntity::update(float dt)
{
  btTransform trans;
  btScalar    m[4 * 4];

  if (m_rigidBody != NULL)
  {
    // m_rigidBody->active(true);
    m_rigidBody->getMotionState()->getWorldTransform(trans);
    trans.getOpenGLMatrix(m);
    Entity::m_model = glm::make_mat4(m);
  }
}

bool PhysicsEntity::load_model(std::string modelFile, std::string textureFile)
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
  btVector3  triArray[3];
  m_triangleMesh = new btTriangleMesh();

  unsigned int tempIndex;

  m_scene = m_importer.ReadFile(modelFile.c_str(),
                                aiProcess_Triangulate | aiProcess_FlipUVs);

  if (m_scene == NULL || m_scene->mRootNode == NULL)
  {
    // Oh! Here's our fun print function! :)
    print("Assimp failed to load model", modelFile,
          m_importer.GetErrorString());
    return false;
  }

  // print("Assimp successfully loaded", modelFile);

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
        aiVector3D position =
            tempMesh->mVertices[tempFaces.mIndices[indexIndex]];
        triArray[indexIndex] = btVector3(position.x, position.y, position.z);
        
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
                   glm::vec2(tempTextCoors.x, tempTextCoors.y),
                   glm::vec3(tempNormal.x, tempNormal.y, tempNormal.z));

        m_vertices.push_back(inputVertex);
        m_indices.push_back(tempIndex);
      }
      m_triangleMesh->addTriangle(triArray[0], triArray[1], triArray[2]);
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

void PhysicsEntity::init(btScalar mass, btVector3 inertia, btVector3 position)
{
  m_mass           = mass;
  m_inertia        = inertia;
  m_collisionShape = new btBvhTriangleMeshShape(m_triangleMesh, true);

  m_shapeMotionState =
      new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), position));
  m_collisionShape->calculateLocalInertia(m_mass, m_inertia);

  btRigidBody::btRigidBodyConstructionInfo shapeRigidBodyCI(
      m_mass, m_shapeMotionState, m_collisionShape, m_inertia);

  m_rigidBody = new btRigidBody(shapeRigidBodyCI);
}

void PhysicsEntity::cleanup() {}
