#pragma once

class TimeManager
{
public:
	TimeManager();
	~TimeManager();

	void Frame();
	void Print();

	void Start();
	void Stop();

	float FPS() const { return framePerSecond; }
	float Running() const { return runningTime; }

	bool Stopped() { return isTimerStopped; }
	float Delta() { return isTimerStopped ? 0.0f : timeElapsed; }

private:
	bool isTimerStopped;
	float timeElapsed;

	INT64 tickPerSecond;
	INT64 currentTime;
	INT64 lastTime;
	INT64 lastFPSUpdate;
	INT64 fpsUpdateInterval;

	UINT frameCount;
	float runningTime;
	float framePerSecond;

};