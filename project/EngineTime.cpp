#include "EngineTime.h"

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

    //auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
    //    sharedInstance->end.time_since_epoch()
    //).count();

  //  std::cout << "frame end " << ms << "\n";

    sharedInstance->start = sharedInstance->end;
}
