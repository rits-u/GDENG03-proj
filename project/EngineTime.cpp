#include "EngineTime.h"
#include <thread>
#include <chrono>

EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::initialize()
{
    sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
    return sharedInstance->deltaTime;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
    sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
    sharedInstance->end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;
    sharedInstance->deltaTime = elapsed_seconds.count();

    const double targetFPS = 1.0f / 60.0f;
    if (sharedInstance->deltaTime < targetFPS)  //if frames rendered too quickly
    {
        double sleepTime = targetFPS - sharedInstance->deltaTime;
        auto sleepMs = std::chrono::duration<double>(sleepTime);
        std::this_thread::sleep_for(sleepMs);   //sleep 

        sharedInstance->end = std::chrono::system_clock::now();
        elapsed_seconds = sharedInstance->end - sharedInstance->start;
        sharedInstance->deltaTime = elapsed_seconds.count();    //update delta time
    }

    sharedInstance->fpsTime += sharedInstance->deltaTime;
    sharedInstance->numFrames += 1;

    if (sharedInstance->fpsTime >= 1.0f)    //1 second
    {
        sharedInstance->FPS = sharedInstance->numFrames;
        sharedInstance->numFrames = 0;
        sharedInstance->fpsTime = 0.0f;
    }

    sharedInstance->start = sharedInstance->end;
}
