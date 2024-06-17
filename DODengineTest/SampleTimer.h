#pragma once

namespace dod
{
	class GameObject;


	class SampleTimer : public GameObject
	{
	public:
		SampleTimer();
		~SampleTimer();

	public:
		virtual void OnCreate()  override;
		virtual void OnEnable()  override;

		virtual void Physics()   override;

		virtual void OnUpdate()  override;

		virtual void Render()	 override;

		virtual void OnDisable() override;
		virtual void OnRelease() override;

	private:
		double _realTimecount;
		double _DeltaTimecount;
	};
}

