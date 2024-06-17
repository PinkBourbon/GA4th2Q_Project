#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include "Timer.h"
#include "GameObject.h"
#include "SoundManager.h"

/// <summary>
/// ������ ���ư��� �ϱ� ���� ���ӿ���
/// ���ӿ�����Ʈ���� ���¸� �ٲٰ�, �����ֱ⿡ ���� ������ ����
/// 
/// ���ӿ����� ��Ģ, ��� ������Ʈ�� �ٸ� ������Ʈ�� �ڱ� �ڽ��� ���� ������ �� ����
/// ��� ������ ��Ź�Ͽ� ������ ���� ó���ϵ��� �����Ͽ��� �Ѵ�.
/// </summary>

namespace dod
{
	class Id2d;

	enum class eObjectState;
	class GameObject;
	class GameEngine;
	class KeyManager;
	class IPhysics;
	struct Transform;
	class SoundManager;

	extern GameEngine g_GameEngine;

	/// <summary>
	/// ����
	/// ������Ʈ Ǯ�� ���ӷ����� ����
	/// ������Ʈ �Լ����� �����ֱ⿡ ���� ���������
	/// </summary>
	class GameEngine
	{
	public:
		GameEngine();
		~GameEngine();

		void GameLoop();

		template<class T>
		T* RegisterGameObject(std::wstring objectName)
		{
			GameObject* ptr = new T();
			ptr->engineptr = this;
			ptr->objectName = objectName;
			_createObjectBuffer.push_back(ptr);

			return static_cast<T*>(ptr);
		}

	public:

		/// <summary>
		/// D2D������ �ʱ�ȭ �Լ��� ȣ���ϴ� �Լ�
		/// </summary>
		void InitializeD2dEngine(HWND hWnd, int screenWidth, int screenHeight);

		void InitializeKeyManger(HWND hWnd);

		void InitializePhysicsEngine();

		void InitializeSoundManager();

		/// <summary>
		/// ���°� �޶��� ������Ʈ�� �ӽ÷� ������ ����
		/// </summary>
		/// <param name="state">�ٲ� ������Ʈ�� ����</param>
		/// <param name="ptr">�ٲ� ������Ʈ�� ������</param>
		void InputChangeStateBuffer(eObjectState state, GameObject* ptr);

		/// <summary>
		/// ������Ʈ�� �����͸� ������ �Լ�
		/// �ߺ��� �̸��� �ϳ��� ã���Ƿ�, ������Ʈ�� �̸��� �ϳ��� ����ϱ�
		/// </summary>
		/// <param name="objectName">�˻��� ������Ʈ�� �̸��� �̿��Ѵ�.</param>
		/// <returns></returns>
		GameObject* GetObjectptr(std::wstring objectName);

		/// <summary>
		/// ������Ʈ�� Ʈ�������� ī�޶�� ����.
		/// ī�޶� ������Ʈ�� �߰� �ϴ°��� �ƴ� ������Ʈ�� ī�޶�� �����ϴ� �Ϳ� ����
		/// </summary>
		void SetCameraObject(Transform* transform);
	private:

		///���� ������Ʈ�� �����ֱ⿡ ���� �� ������ �ݹ��Լ����� ȣ�� ���ִ� �Լ�

		void OnCreate();	// �ʱ�ȭ
		void OnEnable();	// �ʱ�ȭ

		void Physics();		// ��������

		void OnKeyCheck();  //Ű�Է� ���� üũ

		void OnUpdate();	// ���� ����

		void Render();		// ������

		void OnDisable();	// ����
		void OnRelease();	//

		/// <summary>
		/// ������Ʈ�� ���¸� �ٲ��ִ� �Լ�
		/// �Ű������� ������ Ÿ���� ���ۿ� ����ִ� ���̵��� ���¸� �ٲ��ش�.
		/// </summary>
		/// <param name="type">������ Ÿ���� ����</param>
		void setGameObjectState(eObjectState type);

		/// <summary>
		/// �̵����Ǯ ���� ������ƮǮ
		/// ������ ������Ʈ�� ��ٷ� �����Ǵ°��� �ƴ϶�
		/// ���������ӿ� �ش� �Լ��� ���ؼ� ������Ʈ Ǯ�� �̵��ǰ� ����ȴ�.
		/// </summary>
		void moveWaitingPooltoObjectPool();


	public:
		//��ŸŸ�Ӱ� ������ Ÿ��, fps�� �����ϴ� Ÿ�̸�
		Timer timer;

		//���� �Ŵ��� ������
		SoundManager* soundManager;

	private:

		//D2D���� ������
		Id2d* _pD2dEngine;

		//Ű�Է� �Ŵ���
		KeyManager* _pKeyManger;

		//���������� ������
		IPhysics* _physicsEngine;

		//�������� object�� �����ϱ� ���� �����̳�
		std::vector<GameObject*> _objectPool;

		//������Ʈ Ǯ�� �߰� �ϱ� ���� ������� ������Ʈ �����̳�
		std::vector<GameObject*> _createObjectBuffer;

		//Create ���¸� ������ �ִ� ������Ʈ�� ����
		std::vector<GameObject*> _createStateBuffer;

		//Enable ���¸� ������ �ִ� ������Ʈ�� ����
		std::vector<GameObject*> _EnableStateBuffer;

		//Update ���¸� ������ �ִ� ������Ʈ�� ����
		std::vector<GameObject*> _UpdateStateBuffer;

		//Disable ���¸� ������ �ִ� ������Ʈ�� ����
		std::vector<GameObject*> _DisableStateBuffer;

		//Release ���¸� ������ �ִ� ������Ʈ�� ����
		std::vector<GameObject*> _ReleaseStateBuffer;

	};
}