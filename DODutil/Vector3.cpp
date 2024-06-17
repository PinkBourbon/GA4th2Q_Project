#include "Vector3.h"

dod::Vector3::Vector3()
	:x{ 0 }, y{ 0 }, z{ 0 }
{

}
 
dod::Vector3::Vector3(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

dod::Vector3 dod::Vector3::operator+(const Vector3& operand)
{
	Vector3 result;
	result.x = x + operand.x;
	result.y = y + operand.y;
	result.z = z + operand.z;
	return result;
}

dod::Vector3 dod::Vector3::operator-(const Vector3& operand)
{
	Vector3 result;
	result.x = x - operand.x;
	result.y = y - operand.y;
	result.z = z - operand.z;
	return result;
}

dod::Vector3 dod::Vector3::operator*(const float& operand)
{
	Vector3 result;
	result.x = x * operand;
	result.y = y * operand;
	result.z = z * operand;
	return result;
}

dod::Vector3 dod::Vector3::operator/(const float& operand)
{
	Vector3 result;
	result.x = x / operand;
	result.y = y / operand;
	result.z = z / operand;
	return result;
}

float dod::Vector3::GetLength() // 거리 구하기
{
	return sqrt((x * x) + (y * y) + (z * z));
}

dod::Vector3 dod::Vector3::Normalize(Vector3 vector) // 단위벡터
{
	{
		float length = vector.GetLength();
		if (length == 0)
		{
			return vector;
		}
		return (vector / length);
	}
}

float dod::Vector3::Dot(Vector3 a, Vector3 b) // 내적
{
	float result = (a.x * b.x) + (a.y * b.y) + (a.z * b.z);
	return result;
}



dod::Vector3::~Vector3()
{

}
