#pragma once
#include <string>

/// <summary>
/// 모든 객체가 가질 예정
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