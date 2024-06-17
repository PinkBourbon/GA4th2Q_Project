#pragma once
#include <string>
#include <map>
#include "Macro.h"
#include "IComponent.h"

/// <summary>
/// ���� �۾��� ������, ���� �Ǵܿ� ���� 02-10 �η� �輺�� ���Ϸ� �̰�
/// �̰� ����, ���Ӽ� ������ ���� ������ ���Ϸ� ����
/// 
/// �ٸ� ������Ʈ�� ���̽��� �Ǵ� �⺻ Ŭ����
/// �ٸ� ���� ������Ʈ ���۽� �ش� Ŭ������ ����Ͽ� �����
/// 
/// ���ӿ�����Ʈ�� ��Ģ, ��� ������Ʈ�� �ٸ� ������Ʈ�� �ڱ� �ڽ��� ���� ������ �� ����
/// ��� ������ ��Ź�Ͽ� ������ ���� ó���ϵ��� �����Ͽ��� �Ѵ�.
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
	/// ������Ʈ�� ����
	/// �ش� ���¿� �´� �Լ����� ȣ��ǹǷ� ���°� ������ �ٲ��� ��
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
		/// ������Ʈ�� �̸�
		/// </summary>
		std::wstring objectName;

		//Transform transform;
		eObjectState objState;
		
		bool earlyDisabled; //disable()�� �ߺ��Ͽ� ȣ������ �ʵ��� �ϱ� ���� ����

		//���� ������� ���ӿ����� ������
		GameEngine* engineptr;

		virtual void OnCreate() {}	// ������ �� ȣ��Ǵ� �ݹ� �Լ�
		virtual void OnEnable() {}	// Ȱ��ȭ�� �� ȣ��Ǵ� �ݹ� �Լ�

		virtual void OnUpdate() {}	// �������� ���� ȣ��Ǵ� �ݹ� �Լ�

		virtual void OnDisable() {}	// ��Ȱ��ȭ �� �� ȣ��Ǵ� �ݹ� �Լ�
		virtual void OnRelease() {}	// ������ �� ȣ��Ǵ� �ݹ� �Լ�

		/// <summary>
		/// ������Ʈ�� ���� ������ ��û�ϴ� �Լ�.
		/// �ٸ� ������Ʈ�� ���º��� ��û�뵵�ε� ����
		/// ��ٷΰ� �ƴ� ���� �����ӿ� �ٲ� ����
		/// </summary>
		void Enable();
		void Disable();
		void Release();

		/// <summary>
		/// ������Ʈ�� �����͸� �޾ƿ´�.
		/// ��̿��� Ÿ�Կ� �´� ������Ʈ�� ã�´�.
		/// </summary>
		/// <param name="type">������Ʈ�� Ÿ��</param>
		/// <returns></returns>
		template<typename Class>
		inline Class* GetComponent() const;

		/// <summary>
		/// ������Ʈ�� ������Ʈ�� �߰�
		/// </summary>
		/// <param name="pComponent">�߰��� ������Ʈ�� ������</param>
		void AddComponent(IComponent* pComponent);

		/// <summary>
		/// �������� ������Ʈ�� Ž���ؼ� �����͸� ��ȯ
		/// Ž���� �̸� ���
		/// </summary>
		/// <param name="_name">������Ʈ�� �̸�</param>
		/// <returns></returns>
		GameObject* GetGameObject(std::wstring _name);

		/// <summary>
		/// ������Ʈ�� ���������� �˻�
		/// ������Ʈ�� �̸� ���.
		/// ����� true ��ȯ
		/// </summary>
		/// <param name="_name">������Ʈ�� �̸�</param>
		/// <returns></returns>
		bool CheckObjectExiests(std::wstring _name);

	private:
		//������Ʈ�� �迭
		//�迭�� � ������Ʈ�� ��ġ�� �����Ǿ� �ִ�. ex)_componentArray[3] = RenderComponent
		IComponent* _componentArray[componentarraysize];
	};

	template<typename Class>
	inline Class* GameObject::GetComponent() const
	{
		Assert(false, "���ǵ��� ���� ������Ʈ �Դϴ�.");
		return nullptr;
	}

	template<>
	inline dod::Transform* dod::GameObject::GetComponent<dod::Transform>() const
	{
		Transform* component = (Transform*)_componentArray[(int)eComponentType::Transform];
		//Assert(component, "�׳༮�� ���ϴ� Ʈ������ ������Ʈ�� �������� �ʴ´�. ����? Ʈ�������� �и� �����Ҷ����� �־������ٵ� �������� �ʴ´ٰ�?! �װ� ū �����ΰ�? �� ã�ƺ��� �ٶ� �̷��� ��");
		return component;

	}

	template<>
	inline dod::PhysicsComponent* dod::GameObject::GetComponent<dod::PhysicsComponent>() const
	{
		PhysicsComponent* component = (PhysicsComponent*)_componentArray[(int)eComponentType::Physics];
		//Assert(component, "�׳༮�� ���ϴ� ���� ������Ʈ�� �������� �ʴ´�.");
		return component;
	}

	template<>
	inline dod::RenderComponent* dod::GameObject::GetComponent<dod::RenderComponent>() const
	{
		RenderComponent* component = (RenderComponent*)_componentArray[(int)eComponentType::Render];
		//Assert(component, "�׳༮�� ���ϴ� ���� ������Ʈ�� �������� �ʴ´�.");
		return component;
	}

	template<>
	inline dod::KeyComponent* dod::GameObject::GetComponent<dod::KeyComponent>() const
	{
		KeyComponent* component = (KeyComponent*)_componentArray[(int)eComponentType::Controller];
		//Assert(component, "�׳༮�� ���ϴ� Ű ������Ʈ�� �������� �ʴ´�.");
		return component;
	}
}