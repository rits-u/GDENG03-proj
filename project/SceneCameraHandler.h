#pragma once
#include "Camera.h"
#include <vector>

class SceneCameraHandler
{
public:
	static SceneCameraHandler* get();
	static void initialize();
	static void destroy();

	void update();

	Matrix4x4 getSceneCameraViewMatrix();
	void setScreenSize(int width, int height);

	//void set
	Camera* getCamera();
	Camera* getCameraByIndex(int index);
	//void createCameras(int num);
	void addCameraToList(Camera* cam);
	std::vector<Camera*>& getAllCameras();
	void prepareSort();
	std::vector<Camera*> getCamerasSortedByDepth();
	void setActiveCamera(Camera* camera);
	Camera* getTestCamera();

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};
	static SceneCameraHandler* sharedInstance;

	Camera* sceneCamera;
	std::vector<Camera*> cameraList;
	//std::vector<Camera*> sortedCameras;
};

