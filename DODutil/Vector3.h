#pragma once
#include <math.h>
#include <iostream>
namespace dod
{
	struct Vector3
	{
		Vector3();
		~Vector3();

		Vector3(float x, float y, float z);

		Vector3 operator+(const Vector3& operand);
		Vector3 operator-(const Vector3& operand);
		Vector3 operator*(const float& operand); // ��Į�� ����
		Vector3 operator/(const float& operand); // ��Į�� ������

		float GetLength(); // �Ÿ� ���ϱ�

	public:

		static Vector3 Normalize(Vector3 vector); // ��������
		static float Dot(Vector3 a, Vector3 b); // ����



	public:
		float x, y, z;

	};
}
