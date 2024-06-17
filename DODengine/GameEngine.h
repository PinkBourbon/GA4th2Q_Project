#pragma once
#include <vector>
#include <string>
#include <windows.h>
#include "Timer.h"
#include "GameObject.h"
#include "SoundManager.h"

/// <summary>
/// 게임이 돌아가게 하기 위한 게임엔진
/// 게임오브젝트들의 상태를 바꾸고, 생명주기에 따라 돌도록 제작
/// 
/// 게임엔진의 원칙, 모든 오브젝트는 다른 오브젝트나 자기 자신을 직접 변경할 수 없고
/// 모두 엔진에 부탁하여 엔진을 통해 처리하도록 제작하여야 한다.
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
	/// 엔진
	/// 오브젝트 풀과 게임루프가 존재
	/// 오브젝트 함수들을 생명주기에 맞춰 실행시켜줌
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
		/// D2D엔진의 초기화 함수를 호출하는 함수
		/// </summary>
		void InitializeD2dEngine(HWND hWnd, int screenWidth, int screenHeight);

		void InitializeKeyManger(HWND hWnd);

		void InitializePhysicsEngine();

		void InitializeSoundManager();

		/// <summary>
		/// 상태가 달라질 오브젝트를 임시로 저장할 버퍼
		/// </summary>
		/// <param name="state">바뀔 오브젝트의 상태</param>
		/// <param name="ptr">바꿀 오브젝트의 포인터</param>
		void InputChangeStateBuffer(eObjectState state, GameObject* ptr);

		/// <summary>
		/// 오브젝트의 포인터를 보내줄 함수
		/// 중복된 이름은 하나만 찾으므로, 오브젝트의 이름은 하나만 사용하기
		/// </summary>
		/// <param name="objectName">검색시 오브젝트의 이름을 이용한다.</param>
		/// <returns></returns>
		GameObject* GetObjectptr(std::wstring objectName);

		/// <summary>
		/// 오브젝트의 트랜스폼을 카메라로 설정.
		/// 카메라 오브젝트를 추가 하는것이 아닌 오브젝트를 카메라로 지정하는 것에 유의
		/// </summary>
		void SetCameraObject(Transform* transform);
	private:

		///게임 오브젝트의 생명주기에 따라 각 상태의 콜백함수들을 호출 해주는 함수

		void OnCreate();	// 초기화
		void OnEnable();	// 초기화

		void Physics();		// 물리연산

		void OnKeyCheck();  //키입력 상태 체크

		void OnUpdate();	// 게임 로직

		void Render();		// 렌더링

		void OnDisable();	// 해제
		void OnRelease();	//

		/// <summary>
		/// 오브젝트의 상태를 바꿔주는 함수
		/// 매개변수로 지정된 타입의 버퍼에 들어있는 아이들의 상태를 바꿔준다.
		/// </summary>
		/// <param name="type">버퍼의 타입을 선택</param>
		void setGameObjectState(eObjectState type);

		/// <summary>
		/// 이동대기풀 에서 오브젝트풀
		/// 생성된 오브젝트는 곧바로 생성되는것이 아니라
		/// 다음프레임에 해당 함수를 통해서 오브젝트 풀로 이동되고 실행된다.
		/// </summary>
		void moveWaitingPooltoObjectPool();


	public:
		//델타타임과 프레임 타임, fps를 저장하는 타이머
		Timer timer;

		//사운드 매니저 포인터
		SoundManager* soundManager;

	private:

		//D2D엔진 포인터
		Id2d* _pD2dEngine;

		//키입력 매니저
		KeyManager* _pKeyManger;

		//물리엔진의 포인터
		IPhysics* _physicsEngine;

		//관리중인 object를 저장하기 위한 컨테이너
		std::vector<GameObject*> _objectPool;

		//오브젝트 풀에 추가 하기 위해 대기중인 오브젝트 컨테이너
		std::vector<GameObject*> _createObjectBuffer;

		//Create 상태를 가지고 있는 오브젝트의 버퍼
		std::vector<GameObject*> _createStateBuffer;

		//Enable 상태를 가지고 있는 오브젝트의 버퍼
		std::vector<GameObject*> _EnableStateBuffer;

		//Update 상태를 가지고 있는 오브젝트의 버퍼
		std::vector<GameObject*> _UpdateStateBuffer;

		//Disable 상태를 가지고 있는 오브젝트의 버퍼
		std::vector<GameObject*> _DisableStateBuffer;

		//Release 상태를 가지고 있는 오브젝트의 버퍼
		std::vector<GameObject*> _ReleaseStateBuffer;

	};
}