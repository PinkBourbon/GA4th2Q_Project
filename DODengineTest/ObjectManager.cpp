#include <iostream>

#include "GameEngine.h"
#include "SampleUpdate.h"
#include "ObjectManager.h"

dod::ObjectManager::ObjectManager()
{
}

dod::ObjectManager::~ObjectManager()
{
}

void dod::ObjectManager::OnCreate()
{
	//std::cout << "ObjectManger »ý¼º" << std::endl;
}

void dod::ObjectManager::OnEnable()
{
}

void dod::ObjectManager::Physics()
{
}

void dod::ObjectManager::OnUpdate()
{
// 	std::map<std::string, GameObject*>::iterator itr = _objectPool.begin();
// 	for (; itr != _objectPool.end(); itr++)
// 	{
// 		if (itr->second == nullptr)
// 		{
// 			_objectPool.erase(itr);
// 			itr = _objectPool.begin();
// 		}
// 	}
// 
// 	if (CheckObjectExiests("Sample2"))
// 	{
// 		if (GetObject("Sample2")->objState == eObjectState::onDisable)
// 		{
// 			static int i = 0;
// 			i++;
// 
// 			if (i == 5)
// 			{
// 				GetObject("Sample2")->Enable();
// 				i = 0;
// 			}
// 		}
// 
// 		if (GetObject("Sample2")->objState == eObjectState::onUpdate)
// 		{
// 			static int j = 0;
// 
// 			j++;
// 
// 			if (j == 5)
// 			{
// 				GetObject("Sample2")->Disable();
// 
// 				j = 0;
// 			}
// 
// 		}
// 	}
}

void dod::ObjectManager::Render()
{
}

void dod::ObjectManager::OnDisable()
{
}

void dod::ObjectManager::OnRelease()
{
}
