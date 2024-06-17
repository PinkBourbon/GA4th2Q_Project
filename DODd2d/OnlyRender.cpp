#include <typeinfo>

#include "OnlyRender.h"
//#include "Id2d.h"

namespace dod
{
	OnlyRender::OnlyRender()
	{
		_name = typeid(*this).name();
	}

	OnlyRender::~OnlyRender()
	{

	}

	void OnlyRender::Update()
	{

	}

	void OnlyRender::OnPreRender()
	{

	}

	void OnlyRender::OnRender()
	{
		//Id2d::GetInstance()->DrawTextW(0, -20, "component : %s", _name.c_str());
	}

	void OnlyRender::OnPostRender()
	{

	}
}
