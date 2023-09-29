#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = nullptr;

void EngineTime::initialize()
{
	if (sharedInstance == nullptr)
	{
		EngineTime::sharedInstance = new EngineTime;
	}
	else 
	{
		EngineTime::sharedInstance = sharedInstance;
	}

	LogFrameStart();
	LogFrameEnd();
}

double EngineTime::getDeltaTime()
{
	return std::chrono::duration_cast<std::chrono::microseconds>( EngineTime::sharedInstance->start - EngineTime::sharedInstance->end ).count() / 100.0f;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
	delete this;
}

void EngineTime::LogFrameStart()
{
	EngineTime::sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	EngineTime::sharedInstance->end = std::chrono::system_clock::now();
}
