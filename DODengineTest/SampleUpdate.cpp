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
	//std::cout << this->objectName << " �����Ǿ����ϴ�." << std::endl;
}

void dod::SampleUpdate::OnEnable()
{
	//std::cout << this->objectName << " Ȱ��ȭ�Ǿ����ϴ�." << std::endl;
}

void dod::SampleUpdate::Physics()
{
	//std::cout << this->objectName << " ������� �Ǿ����ϴ�." << std::endl;
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

 	//std::cout << this->objectName << " ������Ʈ �Ǿ����ϴ�." << std::endl;
}

void dod::SampleUpdate::Render()
{
	//std::cout << this->objectName << " �׸��� �۾��� �������ϴ�." << std::endl;
}

void dod::SampleUpdate::OnDisable()
{
	//std::cout << this->objectName << " ��Ȱ��ȭ �Ǿ����ϴ�." << std::endl;
}

void dod::SampleUpdate::OnRelease()
{
	//std::cout << this->objectName << " ���ŵǾ����ϴ�." << std::endl;
}
