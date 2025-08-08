#pragma once
#include <string>
#include <vector>
#include <unordered_map>

#include "GameObject.h"
#include "Cube.h"
#include "Plane.h"
#include "Model.h"
#include "Camera.h"

#include "GraphicsEngine.h"
#include "InputSystem.h"
#include "Types.h"

#include "CubeRenderer.h"
#include "PlaneRenderer.h"
#include "QuadRenderer.h"
#include "SphereRenderer.h"
#include "CylinderRenderer.h"
#include "PhysicsComponent.h"



class GameObjectManager
{
public:
	//typedef std::string String;
	//typedef std::vector<GameObject*> List;
	//typedef std::unordered_map<string, GameObject*> HashTable;




	static GameObjectManager* get();
	static void initialize();
	static void destroy();

	GameObject* findObjectByName(string name);
	List getAllObjects();
	int activeObjects();
	//void initialUpdateAll();
	//void updateAllTransformAndBuffers(int viewportWidth, int viewportHeight, VertexShaderPtr vertexShader, PixelShaderPtr pixelShader, int camIndex);
	//void renderAll();
	//void renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, SwapChainPtr sc);
	//void renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, SwapChainPtr sc);
	//void renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, VertexShaderPtr vs, PixelShaderPtr ps, SwapChainPtr sc, TexturePtr tex);
	void renderAllPerCamera(std::vector<Camera*> cameras, int width, int height, SwapChainPtr sc);
	void addObject(GameObject* gameObject);
	void createObject(PrimitiveType type, void* shaderByteCode, size_t sizeShader);
	void deleteObject(GameObject* gameObject);
	void deleteObjectByName(string name);
	void clearSelectedObject();
	void setSelectedObject(string name);
	void setSelectedObject(GameObject* gameObject);
	GameObject* getSelectedObject();

	void createModel(String model, void* shaderByteCode, size_t sizeShader);
	//void addModel(Model* model);:
	string adjustName(string name);
	void processDeletions();

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
	List pendingDeletion;

};

