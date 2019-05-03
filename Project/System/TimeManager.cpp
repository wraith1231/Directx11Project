#include "stdafx.h"
#include "TimeManager.h"

TimeManager::TimeManager()
	: tickPerSecond(0)
	, currentTime(0)
	, lastTime(0)
	, lastFPSUpdate(0)
	, fpsUpdateInterval(0)
	, frameCount(0)
	, runningTime(0)
	, framePerSecond(0)
{
	QueryPerformanceFrequency((LARGE_INTEGER *)&tickPerSecond);
	fpsUpdateInterval = tickPerSecond >> 1;
}

TimeManager::~TimeManager()
{
}

void TimeManager::Frame()
{
	if (isTimerStopped == true) return;

	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);
	timeElapsed = (float)(currentTime - lastTime) / (float)tickPerSecond;
	runningTime += timeElapsed;

	frameCount++;
	if (currentTime - lastFPSUpdate >= fpsUpdateInterval)
	{
		float tempCurrentTime = (float)currentTime / (float)tickPerSecond;
		float tempLastTime = (float)lastFPSUpdate / (float)tickPerSecond;
		framePerSecond = (float)frameCount / (tempCurrentTime - tempLastTime);

		lastFPSUpdate = (INT64)currentTime;
		frameCount = 0;
	}

	lastTime = currentTime;
}

void TimeManager::Print()
{
}

void TimeManager::Start()
{
	if (isTimerStopped == false)
		return;

	QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
	isTimerStopped = false;
}

void TimeManager::Stop()
{
	if (isTimerStopped == true)
		return;

	INT64 stopTime = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&stopTime);
	runningTime += (float)(stopTime - lastTime) / (float)tickPerSecond;
	isTimerStopped = true;
}
