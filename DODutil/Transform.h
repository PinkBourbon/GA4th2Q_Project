#pragma once
#include <math.h>
#include "Matrix3x3.h"
#include "Vector3.h"
#include "IComponent.h"

namespace dod
{
	struct Transform : public IComponent
	{
	public:
		Transform();
		virtual ~Transform();

		Matrix3x3 GetTranformMatrix();
		void SetParent(Transform* newParent);
		void independentFromParent();
		Transform* GetParant();

	public:
		Vector3 scale;		//x, y �࿡ ���� ������ ��
		Vector3 position;	//x, y ��ǥ�� ��ġ ��
		float rotation;		// 360�й� ����		
	private:
		Transform* _pParentTransform;
	};
}