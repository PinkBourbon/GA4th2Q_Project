#pragma once
#include <string>
#include <map>
#include "Macro.h"
#include "IComponent.h"

/// <summary>
/// 최초 작업자 정진수, 팀장 판단에 따라 02-10 부로 배성근 산하로 이관
/// 이관 실패, 종속성 문제로 인해 정진수 산하로 복귀
/// 
/// 다른 오브젝트의 베이스가 되는 기본 클래스
/// 다른 게임 오브젝트 제작시 해당 클래스를 상속하여 만들것
/// 
/// 게임오브젝트의 원칙, 모든 오브젝트는 다른 오브젝트나 자기 자신을 직접 변경할 수 없고
/// 모두 엔진에 부탁하여 엔진을 통해 처리하도록 제작하여야 한다.
/// </summary>


constexpr int componentarraysize = 4;

namespace dod
{
	class GameEngine;
	class IComponent;
	class RenderComponent;
	class PhysicsComponent;
	struct Transform;
	struct KeyComponent;

	/// <summary>
	/// 오브젝트의 상태
	/// 해당 상태에 맞는 함수들이 호출되므로 상태가 꾸준히 바뀌어야 함
	/// </summary>
	enum class eObjectState
	{
		OnCreate,
		OnEnable,
		OnUpdate,
		OnDisable,
		OnRelease
	};

	enum class eComponentType;

	class GameObject
	{
	public:
		GameObject();

		virtual ~GameObject() {};

		/// <summary>
		/// 오브젝트의 이름
		/// </summary>
		std::wstring objectName;

		//Transform transform;
		eObjectState objState;
		
		bool earlyDisabled; //disable()을 중복하여 호출하지 않도록 하기 위한 변수

		//내가 만들어진 게임엔진의 포인터
		GameEngine* engineptr;

		virtual void OnCreate() {}	// 생성될 때 호출되는 콜백 함수
		virtual void OnEnable() {}	// 활성화될 때 호출되는 콜백 함수

		virtual void OnUpdate() {}	// 매프레임 마다 호출되는 콜백 함수

		virtual void OnDisable() {}	// 비활성화 될 때 호출되는 콜백 함수
		virtual void OnRelease() {}	// 해제될 때 호출되는 콜백 함수

		/// <summary>
		/// 오브젝트의 상태 변경을 요청하는 함수.
		/// 다른 오브젝트의 상태변경 요청용도로도 가능
		/// 곧바로가 아닌 다음 프레임에 바뀜에 유의
		/// </summary>
		void Enable();
		void Disable();
		void Release();

		/// <summary>
		/// 컴포넌트의 포인터를 받아온다.
		/// 어레이에서 타입에 맞는 컴포넌트를 찾는다.
		/// </summary>
		/// <param name="type">컴포넌트의 타입</param>
		/// <returns></returns>
		template<typename Class>
		inline Class* GetComponent() const;

		/// <summary>
		/// 컴포넌트를 오브젝트에 추가
		/// </summary>
		/// <param name="pComponent">추가할 컴포넌트의 포인터</param>
		void AddComponent(IComponent* pComponent);

		/// <summary>
		/// 엔진에서 오브젝트를 탐색해서 포인터를 반환
		/// 탐색은 이름 기반
		/// </summary>
		/// <param name="_name">오브젝트의 이름</param>
		/// <returns></returns>
		GameObject* GetGameObject(std::wstring _name);

		/// <summary>
		/// 오브젝트의 존재유무를 검색
		/// 오브젝트의 이름 기반.
		/// 존재시 true 반환
		/// </summary>
		/// <param name="_name">오브젝트의 이름</param>
		/// <returns></returns>
		bool CheckObjectExiests(std::wstring _name);

	private:
		//컴포넌트의 배열
		//배열에 어떤 컴포넌트의 위치는 고정되어 있다. ex)_componentArray[3] = RenderComponent
		IComponent* _componentArray[componentarraysize];
	};

	template<typename Class>
	inline Class* GameObject::GetComponent() const
	{
		Assert(false, "정의되지 않은 컴포넌트 입니다.");
		return nullptr;
	}

	template<>
	inline dod::Transform* dod::GameObject::GetComponent<dod::Transform>() const
	{
		Transform* component = (Transform*)_componentArray[(int)eComponentType::Transform];
		//Assert(component, "네녀석이 원하는 트랜스폼 컴포넌트는 존재하지 않는다. 나닛? 트랜스폼은 분명 생성할때부터 넣어줬을텐데 존재하지 않는다고?! 그건 큰 문제인걸? 잘 찾아보길 바라 미래의 나");
		return component;

	}

	template<>
	inline dod::PhysicsComponent* dod::GameObject::GetComponent<dod::PhysicsComponent>() const
	{
		PhysicsComponent* component = (PhysicsComponent*)_componentArray[(int)eComponentType::Physics];
		//Assert(component, "네녀석이 원하는 물리 컴포넌트는 존재하지 않는다.");
		return component;
	}

	template<>
	inline dod::RenderComponent* dod::GameObject::GetComponent<dod::RenderComponent>() const
	{
		RenderComponent* component = (RenderComponent*)_componentArray[(int)eComponentType::Render];
		//Assert(component, "네녀석이 원하는 렌더 컴포넌트는 존재하지 않는다.");
		return component;
	}

	template<>
	inline dod::KeyComponent* dod::GameObject::GetComponent<dod::KeyComponent>() const
	{
		KeyComponent* component = (KeyComponent*)_componentArray[(int)eComponentType::Controller];
		//Assert(component, "네녀석이 원하는 키 컴포넌트는 존재하지 않는다.");
		return component;
	}
}