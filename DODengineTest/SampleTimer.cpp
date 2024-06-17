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
	std::cout << "timescale�� ������ �����ϴ�. :" << _engineptr->timer.GetTimeScale() << std::endl;
	std::cout << "����Ÿ�� ���� :" << _realTimecount << "�ʰ� �������ϴ�." << std::endl;
	std::cout << "��ŸŸ�� ���� :" << _DeltaTimecount << "�ʰ� �������ϴ�." << std::endl;
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
