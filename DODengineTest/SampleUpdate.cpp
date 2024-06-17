#include <iostream>
#include <random>

#include "SampleUpdate.h"


dod::SampleUpdate::SampleUpdate()
{

}

dod::SampleUpdate::~SampleUpdate()
{

}

void dod::SampleUpdate::OnCreate()
{
	//std::cout << this->objectName << " 생성되었습니다." << std::endl;
}

void dod::SampleUpdate::OnEnable()
{
	//std::cout << this->objectName << " 활성화되었습니다." << std::endl;
}

void dod::SampleUpdate::Physics()
{
	//std::cout << this->objectName << " 물리계산 되었습니다." << std::endl;
}

void dod::SampleUpdate::OnUpdate()
{
// 	if (this->objectName != "Sample2")
// 	{
// 		GetObject("Sample2")->Disable();
// 	}
// 
// 	if (this->objectName != "Sample3")
// 	{
// 		GetObject("Sample3")->Release();
// 	}
// 
// 	if (this->objectName != "Sample1")
// 	{
// 		GetObject("Sample1")->Release();
// 	}

 	//std::cout << this->objectName << " 업데이트 되었습니다." << std::endl;
}

void dod::SampleUpdate::Render()
{
	//std::cout << this->objectName << " 그리기 작업이 끝났습니다." << std::endl;
}

void dod::SampleUpdate::OnDisable()
{
	//std::cout << this->objectName << " 비활성화 되었습니다." << std::endl;
}

void dod::SampleUpdate::OnRelease()
{
	//std::cout << this->objectName << " 제거되었습니다." << std::endl;
}
