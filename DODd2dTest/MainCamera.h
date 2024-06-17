#pragma once
#include "GameObject.h"

namespace dod
{
	struct Transform;

}
class MainCamera : public dod::GameObject
{
public:
	MainCamera();

	virtual void OnCreate();
	virtual void OnEnable();
	virtual void OnUpdate();
	virtual void OnDisable();
	virtual void OnRelease();

	dod::Transform* ReturnTrasform()
	{
		return _transform;
	}


private:
	dod::Transform* _transform;
};
