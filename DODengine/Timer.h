#pragma once
/// <summary>
/// �ð��� ��� ���� Ŭ����
/// �ɹ������� deltaTime�� fps�� �����ϴٰ�
/// getter�� ���� �˷��ִ� ��Ȱ
/// </summary>

namespace dod
{
	class Timer
	{
	public:
		Timer();
		~Timer();

	public:
		/// <summary>
		/// Fps, FrameŸ��, Deltatime�� ������Ʈ �Ѵ�.
		/// ������ �ٽ� �� �Լ��� ȣ�� �� �� ������ ������ Ÿ���� ���� ����
		/// </summary>
		void Update();

		/// <summary>
		/// DeltaTIme�� ���´�.
		/// </summary>
		/// <returns></returns>
		double GetDeltaTime();

		/// <summary>
		/// ������ Ÿ���� ���´�.
		/// </summary>
		/// <returns></returns>
		double GetFrameTime();

		/// <summary>
		/// timescale�� ���´�.
		/// </summary>
		/// <returns></returns>
		double GetTimeScale();

		/// <summary>
		/// deltatime�� timescale�� �����Ѵ�.
		/// </summary>
		void SetTimeScale(double num);
		
		/// <summary>
		/// fps�� ���´�.
		/// </summary>
		/// <returns></returns>
		double GetFps();

	private:
		double _timeScale;
		double _deltaTime;

		double _frameTime;

		double  _lastTime;
		double  _periodFrequency;

		double  _curTime;
		double _fps;
	};
}

