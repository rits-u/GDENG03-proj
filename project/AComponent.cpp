#include "AComponent.h"

AComponent::AComponent(String name, ComponentType type, GameObject* owner)
{
    this->name = name;
    this->type = type;
    this->owner = owner;
}

AComponent::~AComponent()
{
}

void AComponent::attachOwner(GameObject* owner)
{
    this->owner = owner;
}

void AComponent::detachOwner()
{
    this->owner = nullptr;
}

GameObject* AComponent::getOwner()
{
    return this->owner;
}

AComponent::ComponentType AComponent::getType()
{
    return this->type;
}

String AComponent::getName()
{
    return String();
}
