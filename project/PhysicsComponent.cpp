#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(String name, GameObject* owner) : AComponent(name, AComponent::Physics, owner)
{
    BaseComponentSystem::get()->getPhysicsSystem()->registerComponent(this);
    PhysicsCommon* physicsCommon = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsCommon();
    PhysicsWorld* physicsWorld = BaseComponentSystem::get()->getPhysicsSystem()->getPhysicsWorld();

    //create rigid body in the world
    Vector3D scale = this->getOwner()->getLocalScale();
    Transform transform; decimal out[16];
  //  this->getOwner()->convertMatrixToDecimal(out);
  //  transform.setFromOpenGL(out);
    //transform.setFromOpenGL(this->getOwner()->getPhysicsLocalMatrix());
    BoxShape* boxShape = physicsCommon->createBoxShape(Vector3(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2));
    this->rigidBody = physicsWorld->createRigidBody(transform);
    this->rigidBody->addCollider(boxShape, transform);
    this->rigidBody->updateMassPropertiesFromColliders();
    this->rigidBody->setMass(this->mass);
    this->rigidBody->setType(BodyType::DYNAMIC);

    transform = this->rigidBody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);

    this->getOwner()->setLocalMatrix(matrix);


   // this->rigidBody = nullptr;
}

PhysicsComponent::~PhysicsComponent()
{
    AComponent::~AComponent();
    BaseComponentSystem::get()->getPhysicsSystem()->unregisterComponent(this);
}

void PhysicsComponent::perform(float deltaTime)
{
    const Transform transform = this->rigidBody->getTransform();
    float matrix[16];
    transform.getOpenGLMatrix(matrix);
    this->getOwner()->setLocalMatrix(matrix);
}

RigidBody* PhysicsComponent::getRigidBody()
{
    return this->rigidBody;
}
