#include "LevelSerializer.h"

using ordered_json = nlohmann::ordered_json;

LevelSerializer::LevelSerializer()
{
	this->folderName = "Levels/";
	this->levelName = "MyLevel";
}

void LevelSerializer::SaveLevelToFile()
{
	List objList = GameObjectManager::get()->getAllObjects();
	std::vector<ordered_json> jsonObjList;

	ordered_json level;
	level["levelName"] = levelName;
	ordered_json gameObjects = ordered_json::array();

	for (GameObject* g : objList) {
		//name
		ordered_json object;
		object["objectName"] = g->getName();

		//transform
		ordered_json transform;
		Vector3D pos = g->getPosition();
		transform["position"] = { pos.m_x, pos.m_y, pos.m_z };

		Vector3D rot = g->getRotation();
		transform["rotation"] = { rot.m_x, rot.m_y, rot.m_z };

		Vector3D scale = g->getScale();
		transform["scale"] = { scale.m_x, scale.m_y, scale.m_z };
		object["transform"] = transform;

		//components
		ComponentList compList = g->getComponents();
		ordered_json components;

		for (Component* c : compList) {
			//ordered_json component;
			if (c->type == ComponentType::RENDERER) {
				ordered_json renderer;
				renderer["componentName"] = c->getName();
				renderer["primitiveType"] = toString(g->getPrimitiveType());
				components["renderer"] = renderer;
			}

			if (c->type == ComponentType::PHYSICS) {
				ordered_json physics;
				physics["componentName"] = c->getName();
				PhysicsComponent* p6 = dynamic_cast<PhysicsComponent*>(c);
				if (p6) {
					ordered_json rigidBody;
					//rigidBody["bodyType"] = toString(p6->getBodyType());
					rigidBody["mass"] = p6->mass;
					rigidBody["useGravity"] = p6->useGravity;
					physics["rigidBody"] = rigidBody;

					ordered_json collider;
					collider["shape"] = p6->shape;
					physics["collider"] = collider;
				}
				
				components["physics"] = physics;
			}

			//components.push_back(component);
		}

		object["components"] = components;
		gameObjects.push_back(object);

	}

	level["gameObjects"] = gameObjects;

	std::ofstream outputFile(folderName + levelName + ".level");
	if (outputFile.is_open()) {
		outputFile << std::setw(4) << level << std::endl;
		outputFile.close();
	}
	else {
		std::cout << "file cannot be saved" << std::endl;
	}
}

std::string LevelSerializer::toString(PrimitiveType type)
{
	switch (type) {
		case PrimitiveType::CUBE: return "CUBE";
		case PrimitiveType::PLANE: return "PLANE";
		case PrimitiveType::QUAD: return "QUAD";
		case PrimitiveType::SPHERE: return "SPHERE";
		case PrimitiveType::CYLINDER: return "CYLINDER";
		case PrimitiveType::CAPSULE: return "CAPSULE";
	}
}

std::string LevelSerializer::toString(BodyType type)
{
	switch (type) {
		case BodyType::STATIC: return "STATIC";
		case BodyType::DYNAMIC: return "DYNAMIC";
		case BodyType::KINEMATIC: return "KINEMATIC";
	}
}
