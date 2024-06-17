#pragma once
#include <string>

/// <summary>
/// ��� ��ü�� ���� ����
/// </summary>
namespace dod
{
	class OnlyRender
	{
	public:
		OnlyRender();
		virtual ~OnlyRender();

		virtual void Update();
		virtual void OnPreRender();
		virtual void OnRender();
		virtual void OnPostRender();

	protected:
		std::string _name;
	};
}