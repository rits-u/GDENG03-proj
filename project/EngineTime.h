#pragma once

#include <iostream>
#include <chrono>
#include <ctime>

class Window;

class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const&) {};
	static EngineTime* sharedInstance;

private:
	static void LogFrameStart();
	static void LogFrameEnd();

private:
	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0f;
	int numFrames = 0;
	double fpsTime = 0.0f;
	int FPS = 0;


private:
	friend class Window;

};

