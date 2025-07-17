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

	//void set
	Camera* getCamera();
	Camera* getCameraByIndex(int index);
	void addCameraToList(Camera* cam);
	std::vector<Camera*>& getAllCameras();
	void sortCamerasByDepth();
	void setActiveCamera(Camera* camera);

	//Camera* getTestCamera();
	//std::vector<Camera*> getCamerasSortedByDepth();
	//void createCameras(int num);
	// 	void prepareSort();

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

