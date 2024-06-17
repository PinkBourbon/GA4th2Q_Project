#include <iostream>
#include "GameEngine.h"
#include "GameObject.h"
#include "SampleTimer.h"
#include "Timer.h"


dod::SampleTimer::SampleTimer()
	: _realTimecount(0), _DeltaTimecount(0)
{

}

dod::SampleTimer::~SampleTimer()
{

}

void dod::SampleTimer::OnCreate()
{

}

void dod::SampleTimer::OnEnable()
{
}

void dod::SampleTimer::Physics()
{
}

void dod::SampleTimer::OnUpdate()
{
	_realTimecount += (_engineptr->timer.GetFrameTime());
	_DeltaTimecount += (_engineptr->timer.GetDeltaTime());
	
	std::cout << std::fixed;
	std::cout.precision(3);
	std::cout << "timescale은 다음과 같습니다. :" << _engineptr->timer.GetTimeScale() << std::endl;
	std::cout << "리얼타임 기준 :" << _realTimecount << "초가 지났습니다." << std::endl;
	std::cout << "델타타임 기준 :" << _DeltaTimecount << "초가 지났습니다." << std::endl;
}

void dod::SampleTimer::Render()
{

}

void dod::SampleTimer::OnDisable()
{

}

void dod::SampleTimer::OnRelease()
{

}
