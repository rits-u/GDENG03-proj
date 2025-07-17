#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "GameObject.h"
#include "Cube.h"
#include "Plane.h"
#include "Camera.h"

#include "GraphicsEngine.h"

class GameObjectManager
{
public:
	//typedef std::string String;
	typedef std::vector<GameObject*> List;
	typedef std::unordered_map<string, GameObject*> HashTable;

	enum PrimitiveType {
		CUBE,
		PLANE
	};

	static GameObjectManager* get();
	static void initialize();
	static void destroy();

	GameObject* findObjectByName(string name);
	List getAllObjects();
	int activeObjects();
	void updateAll();
	//void updateAllTransformAndBuffers();
	void updateAllTransformAndBuffers(int viewportWidth, int viewportHeight, VertexShaderPtr vertexShader, PixelShaderPtr pixelShader, int camIndex);
	void renderAll();
	//void renderAll(int viewportWidth, int viewportHeight, VertexShaderPtr vertexShader, PixelShaderPtr pixelShader);
	void renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, SwapChainPtr sc);
	void addObject(GameObject* gameObject);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(GameObject* gameObject);
	void deleteObjectByName(string name);
	void setSelectedObject(string name);
	void setSelectedObject(GameObject* gameObject);
	GameObject* getSelectedObject();

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator=(GameObjectManager const&) {};
	static GameObjectManager* sharedInstance;

private:
	List gameObjectList;
	HashTable gameObjectTable;
	GameObject* selectedObject;

};

