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
		Vector3 operator*(const float& operand); // ½ºÄ®¶ó °ö¼À
		Vector3 operator/(const float& operand); // ½ºÄ®¶ó ³ª´°¼À

		float GetLength(); // °Å¸® ±¸ÇÏ±â

	public:

		static Vector3 Normalize(Vector3 vector); // ´ÜÀ§º¤ÅÍ
		static float Dot(Vector3 a, Vector3 b); // ³»Àû



	public:
		float x, y, z;

	};
}
