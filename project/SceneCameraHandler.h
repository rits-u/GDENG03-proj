#pragma once
#include "Camera.h"
#include <vector>

class SceneCameraHandler
{
public:
	static SceneCameraHandler* get();
	static void initialize();
	static void destroy();

	void updateAllCameras();

	Matrix4x4 getSceneCameraViewMatrix();
	void setScreenSize(int width, int height);
	void setScreenSizeForAllCameras(int width, int height);

	Camera* getCamera();
	Camera* getCameraByIndex(int index);
	void addCameraToList(Camera* cam);
	std::vector<Camera*>& getAllCameras();
	void sortCamerasByDepth();
	void setActiveCamera(Camera* camera);

private:
	SceneCameraHandler();
	~SceneCameraHandler();
	SceneCameraHandler(SceneCameraHandler const&) {};
	SceneCameraHandler& operator=(SceneCameraHandler const&) {};
	static SceneCameraHandler* sharedInstance;

	Camera* sceneCamera;
	std::vector<Camera*> cameraList;
};

