#pragma once
#include <map>
#include "GameObject.h"

namespace dod
{
	class ObjectManager : public GameObject
	{
	public:
		ObjectManager();
		~ObjectManager();

	public:
		virtual void OnCreate()  override;
		virtual void OnEnable()  override;

		virtual void Physics()   override;

		virtual void OnUpdate()  override;

		virtual void Render()	 override;

		virtual void OnDisable() override;
		virtual void OnRelease() override;

	private:
		std::map<std::string,GameObject*> _objectPool;
	};
}

