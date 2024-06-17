#pragma once
#include "Macro.h"

/// <summary>
/// 최초 작업자 정진수, 팀장 판단에 따라 02-09 부로 배성근 산하로 이관
/// 컴포넌트의 인터페이스(아님)를 작업하는 공간이므로 실제 컴포넌트를 생성시
/// icomponent를 상속받아 쓸것.
/// </summary>
namespace dod
{
	/// <summary>
	/// 컴포넌트의 타입을 지정
	/// 한 오브젝트는 하나의 타입의 컴포넌트 밖에 가지지 못한다.
	/// </summary>
	enum class eComponentType
	{
		Transform,
		Physics,
		Render,
		Controller
	};

	/// <summary>
	/// 새로운 타입의 컴포넌트가 추가될때 수정해야 할것.
	/// IComponent.h의 eComponentType
	/// GameObject.h의 constexpr int componentarraysize = 5;
	/// GameObject.cpp의 AddComponent(IComponent* pComponent)
	/// GameObject.cpp의 GetComponent(eComponentType type))
	/// </summary>

	class GameObject;

	/// <summary>
	/// 컴포넌트의 인터페이스
	/// </summary>
	class IComponent
	{
		friend class GameObject;

	public:
		IComponent(eComponentType componentType)
			: _componentType(componentType), _pObejct(nullptr)
		{}

		virtual ~IComponent() = 0 {};

	public:
		//함수부

		//이 컴포넌트가 포함된 오브젝트의 포인터르 전달한다.
		GameObject* GetObject()
		{
			return _pObejct;
		}

	public:
		//변수부

		//해당 컴포넌트의 타입
		eComponentType _componentType;

		template<class C>
		void Enable()
		{

		}

		template<class C>
		void Disable()
		{

		}

	private:
		//변수부

		//컴포넌트가 적용된 오브젝트의 포인터
		 GameObject* _pObejct;
	};
}
