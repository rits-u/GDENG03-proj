#include "PhysicsComponent.h"
#include <algorithm>


PhysicsComponent::PhysicsComponent(BodyType type) : Component(ComponentType::PHYSICS)
{
    this->mass = 1000.0f;
    this->rigidBody = nullptr;
    this->bodyType = BodyType::STATIC;
    PhysicsSystem::get()->addPhysicsComponent(this);
}
        
void PhysicsComponent::init()
{
    PhysicsSystem* system = PhysicsSystem::get();
    PhysicsCommon* physicsCommon = system->getPhysicsCommon();
    PhysicsWorld* physicsWorld = system->getPhysicsWorld();

    //create rigid body
    Vector3D posTemp = this->getOwner()->getPosition();
    Vector3 position = Vector3(posTemp.m_x, posTemp.m_y, posTemp.m_z);
    Quaternion quaternion = EulerToQuaternion(this->getOwner()->getRotation());
    Transform transform(position, quaternion);

    this->rigidBody = physicsWorld->createRigidBody(transform);
    this->rigidBody->setType(this->bodyType);
    this->rigidBody->addCollider(this->createColliderShape(this->getOwner()->getPrimitiveType()), Transform::identity());

    if (this->bodyType == BodyType::DYNAMIC) {
        this->rigidBody->updateMassPropertiesFromColliders();
        this->rigidBody->setMass(this->mass);
    }
}

void PhysicsComponent::update()
{
    if (this->rigidBody->getType() == BodyType::DYNAMIC) {
        Transform transform = this->rigidBody->getTransform();
        Vector3 position = transform.getPosition();
        Quaternion quaternion = transform.getOrientation();
        this->getOwner()->setPosition(Vector3D(position.x, position.y, position.z));
        this->getOwner()->setRotation(Vector3D(QuaternionToEuler(quaternion)));
    }
    else if (this->rigidBody->getType() == BodyType::STATIC) {
        Vector3D temp = this->getOwner()->getPosition();
        Vector3 position = Vector3(temp.m_x, temp.m_y, temp.m_z);
        Quaternion rotation = EulerToQuaternion(this->getOwner()->getRotation());
        this->rigidBody->setTransform(Transform(position, rotation));
    }
}

void PhysicsComponent::release()
{
}

RigidBody* PhysicsComponent::getRigidBody()
{
    return this->rigidBody;
}

void PhysicsComponent::setBodyType(BodyType type)
{
    this->bodyType = type;
    this->rigidBody->setType(this->bodyType);
}

BodyType PhysicsComponent::getBodyType()
{
    return this->bodyType;
}

CollisionShape* PhysicsComponent::createColliderShape(PrimitiveType type)
{
    Vector3D scale = this->getOwner()->getScale();
    PhysicsCommon* physicsCommon = PhysicsSystem::get()->getPhysicsCommon();

    switch (type) {
    case PrimitiveType::CUBE:
    {
        Vector3 vecShape(scale.m_x / 2, scale.m_y / 2, scale.m_z / 2);
        return physicsCommon->createBoxShape(vecShape);
    }
    case PrimitiveType::PLANE: {
        float size = this->getOwner()->getComponent<Renderer>()->getSize();
        float halfWidth = 0.5f * size * scale.m_x;
        float halfDepth = 0.5f * size * scale.m_z;
        Vector3 vecShape(halfWidth, 0.1f, halfDepth);
        return physicsCommon->createBoxShape(vecShape);
    }
    case PrimitiveType::QUAD: {
        float size = this->getOwner()->getComponent<Renderer>()->getSize();
        float halfWidth = 0.5f * size * scale.m_x;
        float halfHeight = 0.5f * size * scale.m_y;
        Vector3 vecShape(halfWidth, halfHeight, 0.1f);
        return physicsCommon->createBoxShape(vecShape);
    }
    case PrimitiveType::SPHERE:
    {
        std::cout << "before getting size" << std::endl;
        float radius = this->getOwner()->getComponent<Renderer>()->getRadius();
        std::cout << "after" << std::endl;
        return physicsCommon->createSphereShape(radius);
    }
    case PrimitiveType::CYLINDER:
        CylinderRenderer* renderer = (CylinderRenderer*)this->getOwner()->getComponent<Renderer>();
        float radius = renderer->getRadius();
        float height = std::max(renderer->getSize() - 2.0f * radius, 0.01f);
        return physicsCommon->createCapsuleShape(radius, height);
    }

    return nullptr;
}

reactphysics3d::Quaternion PhysicsComponent::EulerToQuaternion(Vector3D euler)
{
    double cy = cos(euler.m_x * 0.5);
    double sy = sin(euler.m_x * 0.5);
    double cp = cos(euler.m_y * 0.5);
    double sp = sin(euler.m_y * 0.5);
    double cr = cos(euler.m_z * 0.5);
    double sr = sin(euler.m_z * 0.5);

    reactphysics3d::Quaternion q;
    q.w = cr * cp * cy + sr * sp * sy;
    q.x = sr * cp * cy - cr * sp * sy;
    q.y = cr * sp * cy + sr * cp * sy;
    q.z = cr * cp * sy - sr * sp * cy;

    return q;
}

Vector3D PhysicsComponent::QuaternionToEuler(reactphysics3d::Quaternion q)
{
    double w = q.w; double x = q.x;  double y = q.y;  double z = q.z;
    double roll = atan2(2 * (w * x + y * z), 1 - 2 * (x * x + y * y));
    double pitch = std::asin(std::clamp(2 * (w * y - z * x), -1.0, 1.0));
    double yaw = atan2(2 * (w * z + x * y), 1 - 2 * (y * y + z * z));

    return Vector3D(roll, pitch, yaw);
}
