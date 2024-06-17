#pragma once
#include "Macro.h"

/// <summary>
/// ���� �۾��� ������, ���� �Ǵܿ� ���� 02-09 �η� �輺�� ���Ϸ� �̰�
/// ������Ʈ�� �������̽�(�ƴ�)�� �۾��ϴ� �����̹Ƿ� ���� ������Ʈ�� ������
/// icomponent�� ��ӹ޾� ����.
/// </summary>
namespace dod
{
	/// <summary>
	/// ������Ʈ�� Ÿ���� ����
	/// �� ������Ʈ�� �ϳ��� Ÿ���� ������Ʈ �ۿ� ������ ���Ѵ�.
	/// </summary>
	enum class eComponentType
	{
		Transform,
		Physics,
		Render,
		Controller
	};

	/// <summary>
	/// ���ο� Ÿ���� ������Ʈ�� �߰��ɶ� �����ؾ� �Ұ�.
	/// IComponent.h�� eComponentType
	/// GameObject.h�� constexpr int componentarraysize = 5;
	/// GameObject.cpp�� AddComponent(IComponent* pComponent)
	/// GameObject.cpp�� GetComponent(eComponentType type))
	/// </summary>

	class GameObject;

	/// <summary>
	/// ������Ʈ�� �������̽�
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
		//�Լ���

		//�� ������Ʈ�� ���Ե� ������Ʈ�� �����͸� �����Ѵ�.
		GameObject* GetObject()
		{
			return _pObejct;
		}

	public:
		//������

		//�ش� ������Ʈ�� Ÿ��
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
		//������

		//������Ʈ�� ����� ������Ʈ�� ������
		 GameObject* _pObejct;
	};
}
