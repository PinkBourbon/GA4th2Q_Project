#pragma once
#include <initializer_list>
#include "Vector3.h"

namespace dod {
	struct Matrix3x3
	{
	public:
		Matrix3x3();
		Matrix3x3(std::initializer_list<float> list);

		Matrix3x3 operator+(const Matrix3x3& operand);
		Matrix3x3 operator-(const Matrix3x3& operand);
		Matrix3x3 operator*(const float& operand);
		Vector3 operator*(const Vector3& operand);
		Matrix3x3 operator*(const Matrix3x3& operand);
		Matrix3x3 operator/(const float& operand);
		Matrix3x3 operator/(const Matrix3x3& operand);


	public:
		static Matrix3x3 Identity();
		Matrix3x3 Inverse() const;

	public:
		float matrix[3][3];

	};
}

