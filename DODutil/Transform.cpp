#include "Transform.h"

dod::Transform::Transform()
	: scale{ 0,0,0 }, position{ 0, 0, 0 }, rotation{ 0 }
	,IComponent(eComponentType::Transform), _pParentTransform(nullptr)
{

}

dod::Transform::~Transform()
{

}
dod::Matrix3x3 dod::Transform::GetTranformMatrix()
{

	float radian = rotation * (3.141592f / 180);
	Matrix3x3 matrixT =
	{
		scale.x * cos(radian)	 , -scale.x * sin(radian)	, 0,
		scale.y * sin(radian)	 , scale.y  * cos(radian)	, 0,
		position.x				 , position.y				, 1
	};
	// 행렬은 교환법칙이 성립이 안된다. 그래서 순서를 잘 맞춰야 한다.
	// SRT

	if (_pParentTransform != nullptr)
	{
		matrixT = matrixT * _pParentTransform->GetTranformMatrix();
	}

	return matrixT;
}

void dod::Transform::SetParent(Transform* newParent)
{
	_pParentTransform = newParent;
}

void dod::Transform::independentFromParent()
{
	_pParentTransform = nullptr;
}

dod::Transform* dod::Transform::GetParant()
{
	return _pParentTransform;
}

