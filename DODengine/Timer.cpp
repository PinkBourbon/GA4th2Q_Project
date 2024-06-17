
#include <cmath>
#include <windows.h>

#include "Timer.h"

dod::Timer timer;

dod::Timer::Timer()
	:_deltaTime(0.0)
	,_timeScale(1.0)
	, _lastTime(0.0)
	, _periodFrequency(0.0)
	, _curTime(0.0)
	, _fps(0.0)
	, _frameTime(0.0)
{
	QueryPerformanceFrequency((LARGE_INTEGER*)&_periodFrequency);
	QueryPerformanceCounter((LARGE_INTEGER*)&_lastTime);
}

dod::Timer::~Timer()
{

}

void dod::Timer::Update()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&_curTime);
	_frameTime = (double)((_curTime - _lastTime) / _periodFrequency);
	_lastTime = _curTime;
	_fps = 1.0 / _frameTime;
}

double dod::Timer::GetDeltaTime()
{
	return _frameTime * _timeScale;                   
}

double dod::Timer::GetFrameTime()
{
	return _frameTime;
}

double dod::Timer::GetTimeScale()
{
	return _timeScale;
}

void dod::Timer::SetTimeScale(double num)
{
	_timeScale = num;
}

double dod::Timer::GetFps()
{
	return _fps;
}
