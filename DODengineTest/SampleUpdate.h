#pragma once
#include "GameObject.h"

namespace dod
{
	class GameObject;

	class SampleUpdate : public GameObject
	{
	public:
		SampleUpdate();
		~SampleUpdate();

		virtual void OnCreate() override;
		virtual void OnEnable() override;

		virtual void Physics() override;

		virtual void OnUpdate() override;

		virtual void Render() override;

		virtual void OnDisable() override;
		virtual void OnRelease() override;
	};
}