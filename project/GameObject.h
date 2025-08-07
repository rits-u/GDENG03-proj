#pragma once
#include <string>
#include "Vector3D.h"
#include "Vector2D.h"
#include "Matrix4x4.h"
#include "Prerequisites.h"
#include "Types.h"
#include "Constant.h"
#include "MyTransform.h"
#include "Component.h"
#include <vector>
//#include "Camera.h"

//using namespace std;

class VertexShader;
class PixelShader;

enum Layer : unsigned int {
	DEFAULT = 1 << 0,
	UI = 1 << 2,
	DEBUG = 1 << 1,
};

/*
	bitmask with DEFAULT and DEBUG
	0 0 0 0   0 0 1 1

	with UI
	0 0 0 0   0 1 0 0

	DEFAULT ONLY
	0 0 0 0   0 0 0 1
*/


//class Component;
class GameObject
{

public:
	GameObject(String name);
	~GameObject();

	virtual void update(float deltaTime) {};
	virtual void draw(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps) {};
	virtual void updateTransformAndBuffers(int width, int height, int camIndex) {};
	virtual void updateTransformAndBuffers(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, int camIndex) {};
	//virtual void updateTransformAndBuffers(int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, int camIndex) = 0;
	virtual void render() {};

	void setPosition(float x, float y, float z);
	void setPosition(Vector3D pos);
	Vector3D getPosition();

	void setScale(float x, float y, float z);
	void setScale(Vector3D scale);
	Vector3D getScale();

	void setRotation(float x, float y, float z);
	void setRotation(Vector3D rot);
	Vector3D getRotation();
	Matrix4x4 getWorldMatrix();
	MyTransform getTransform();

	void setLayer(unsigned int layer);
	unsigned int getLayer();

	void setEnabled(bool enabled);
	bool isEnabled();

	void setName(String name);
	String getName();

	constant getConstant();

	//ComponentList getComponents();
	ComponentList& getComponents();

public:
	template <typename T, typename... Args> inline
		typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type
		addComponent(Args&&... args)
	{
		for (auto c : components) {
			/*if (typeid(*c) == typeid(T))
				return nullptr;*/
			if (dynamic_cast<T*>(c) != nullptr) // Match base or derived
				return nullptr;

		}
		T* component = new T(std::forward<Args>(args)...);
		component->setOwner(this);
		components.push_back(component);
		component->init();
		return component;
	}

	template <typename T> inline
		typename std::enable_if<std::is_base_of<Component, T>::value, T*>::type
		getComponent()
	{
		for (auto c : components) {
			if (T* result = dynamic_cast<T*>(c))
				return result;
		}
		return nullptr;
	}

	template <typename T> inline
		typename std::enable_if<std::is_base_of<Component, T>::value, void>::type
		removeComponent()
	{
		erase_if(components, [](Component* c) {
			return typeid(*c) == typeid(T);
		});
	}
//
//public:
//	struct vertex {
//		Vector3D position;
//		Vector2D texCoord;
//	};



protected:
	ComponentList components;
	String name;
	MyTransform transform;
	constant cc;
	unsigned int layer;
	bool enabled;
};

