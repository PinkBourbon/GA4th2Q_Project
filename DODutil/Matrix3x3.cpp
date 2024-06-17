#include "Matrix3x3.h"

dod::Matrix3x3::Matrix3x3() : matrix{ {0.0f, 0.0f , 0.0f},{0.0f, 0.0f, 0.0f},{0.0f, 0.0f, 0.0f} }
{

}




dod::Matrix3x3::Matrix3x3(std::initializer_list<float> list) : matrix{ {1.0f, 0.0f , 0.0f},{0.0f, 1.0f, 0.0f},{0.0f, 0.0f, 1.0f} }
{
	int i = 0;
	int j = 0;
	for (auto iter = list.begin(); iter != list.end(); ++iter)
	{
		matrix[i][j] = *iter;
		j++;
		if (j > 2)
		{
			j = 0;
			i++;
		}
	}
}



dod::Matrix3x3 dod::Matrix3x3::operator+(const Matrix3x3& operand)
{
	return Matrix3x3
	{
		this->matrix[0][0] + operand.matrix[0][0], this->matrix[0][1] + operand.matrix[0][1], this->matrix[0][2] + operand.matrix[0][2],
		this->matrix[1][0] + operand.matrix[1][0], this->matrix[1][1] + operand.matrix[1][1], this->matrix[1][2] + operand.matrix[1][2],
		this->matrix[2][0] + operand.matrix[2][0], this->matrix[2][1] + operand.matrix[2][1], this->matrix[2][2] + operand.matrix[2][2]
	};
}

dod::Matrix3x3 dod::Matrix3x3::operator-(const Matrix3x3& operand)
{
	return Matrix3x3
	{
		this->matrix[0][0] - operand.matrix[0][0], this->matrix[0][1] - operand.matrix[0][1], this->matrix[0][2] - operand.matrix[0][2],
		this->matrix[1][0] - operand.matrix[1][0], this->matrix[1][1] - operand.matrix[1][1], this->matrix[1][2] - operand.matrix[1][2],
		this->matrix[2][0] - operand.matrix[2][0], this->matrix[2][1] - operand.matrix[2][1], this->matrix[2][2] - operand.matrix[2][2]
	};
};

dod::Matrix3x3 dod::Matrix3x3::operator*(const float& operand)
{
	return Matrix3x3
	{
		this->matrix[0][0] * operand, this->matrix[0][1] * operand, this->matrix[0][2] * operand,
		this->matrix[1][0] * operand, this->matrix[1][1] * operand, this->matrix[1][2] * operand,
		this->matrix[2][0] * operand, this->matrix[2][1] * operand, this->matrix[2][2] * operand
	};
}

dod::Vector3 dod::Matrix3x3::operator*(const Vector3& operand)
{
	Vector3 result = Vector3
	(
		{ this->matrix[0][0] * operand.x + this->matrix[0][1] * operand.y + this->matrix[0][2] * operand.z },
		{ this->matrix[1][0] * operand.x + this->matrix[1][1] * operand.y + this->matrix[1][2] * operand.z },
		{ this->matrix[2][0] * operand.x + this->matrix[2][1] * operand.y + this->matrix[2][2] * operand.z }
	);
	return result;

}

dod::Matrix3x3 dod::Matrix3x3::operator*(const Matrix3x3& operand)
{
	return Matrix3x3
	{
		this->matrix[0][0] * operand.matrix[0][0] + this->matrix[0][1] * operand.matrix[1][0] + this->matrix[0][2] * operand.matrix[2][0],
		this->matrix[0][0] * operand.matrix[0][1] + this->matrix[0][1] * operand.matrix[1][1] + this->matrix[0][2] * operand.matrix[2][1],
		this->matrix[0][0] * operand.matrix[0][2] + this->matrix[0][1] * operand.matrix[1][2] + this->matrix[0][2] * operand.matrix[2][2],

		this->matrix[1][0] * operand.matrix[0][0] + this->matrix[1][1] * operand.matrix[1][0] + this->matrix[1][2] * operand.matrix[2][0],
		this->matrix[1][0] * operand.matrix[0][1] + this->matrix[1][1] * operand.matrix[1][1] + this->matrix[1][2] * operand.matrix[2][1],
		this->matrix[1][0] * operand.matrix[0][2] + this->matrix[1][1] * operand.matrix[1][2] + this->matrix[1][2] * operand.matrix[2][2],

		this->matrix[2][0] * operand.matrix[0][0] + this->matrix[2][1] * operand.matrix[1][0] + this->matrix[2][2] * operand.matrix[2][0],
		this->matrix[2][0] * operand.matrix[0][1] + this->matrix[2][1] * operand.matrix[1][1] + this->matrix[2][2] * operand.matrix[2][1],
		this->matrix[2][0] * operand.matrix[0][2] + this->matrix[2][1] * operand.matrix[1][2] + this->matrix[2][2] * operand.matrix[2][2]
	};
}

dod::Matrix3x3 dod::Matrix3x3::operator/(const float& operand)
{
	return Matrix3x3
	{
		this->matrix[0][0] / operand, this->matrix[0][1] * operand, this->matrix[0][2] * operand,
		this->matrix[1][0] / operand, this->matrix[1][1] * operand, this->matrix[1][2] * operand,
		this->matrix[2][0] / operand, this->matrix[2][1] * operand, this->matrix[2][2] * operand
	};
}

dod::Matrix3x3 dod::Matrix3x3::operator/(const Matrix3x3& operand)
{
	float a = operand.matrix[0][0];
	float b = operand.matrix[0][1];
	float c = operand.matrix[0][2];
	float d = operand.matrix[1][0];
	float e = operand.matrix[1][1];
	float f = operand.matrix[1][2];
	float g = operand.matrix[2][0];
	float h = operand.matrix[2][1];
	float i = operand.matrix[2][2];
	float set = 
		b * b * d * d + 
		b * b * f * f * g * g + 
		c * c * d * d * h * h + 
		a * a * f * f * h * h - 
		2 * a * c * d * f * h * h - 
		2 * a * b * f * f * g * h + 
		2 * b * c * d * f * g * h + 
		a * a * e * e + 
		c * c * g * g * e * e - 
		2 * a * b * d * e - 
		2 * b * c * f * g * g * e - 
		2 * c * c * d * g * h * e + 
		2 * a * c * f * g * h * e;
	Matrix3x3 inverseMatrix
	{
		a * f * f * h * h 
		- c * d * f * h * h 
		- i * b * d * f * h 
		- b * f * f * g * h 
		+ a * e * e 
		- i * c * g * e * e 
		- b * d * e 
		+ i * b * f * g * e 
		+ i * c * d * h * e 
		+ c * f * g * h * e, 

		b * b * d 
		- i * b * b * f * g 
		+ c * c * d * h * h 
		- a * c * f * h * h 
		+ i * a * b * f * h 
		+ b * c * f * g * h 
		- a * b * e 
		+ i * b * c * g * e 
		- i * a * c * h * e 
		- c * c * g * h * e, 

		i * b * b * d * f 
		+ b * b * f * f * g 
		- a * b * f * f * h 
		+ b * c * d * f * h 
		+ i * a * c * e * e 
		+ c * c * g * e * e 
		- i * b * c * d * e 
		- i * a * b * f * e
		- 2 * b * c * f * g * e 
		- c * c * d * h * e 
		+ a * c * f * h * e,

		b * d * d 
		+ b * f * f * g * g 
		- i * c * d * d * h 
		+ i * a * d * f * h 
		- a * f * f * g * h 
		+ c * d * f * g * h 
		- a * d * e 
		- c * f * g * g * e 
		+ i * c * d * g * e 
		- i * a * f * g * e, 

		-a * b * d 
		- b * c * f * g * g 
		- i * b * c * d * g 
		+ i * a * b * f * g 
		+ i * a * c * d * h 
		- i * a * a * f * h 
		- c * c * d * g * h 
		+ a * c * f * g * h 
		+ a * a * e 
		+ c * c * g * g * e,

		i * b * c * d * d 
		- i * a * b * d * f 
		- a * b * f * f * g 
		+ b * c * d * f * g 
		+ c * c * d * d * h 
		+ a * a * f * f * h 
		- 2 * a * c * d * f * h 
		- i * a * c * d * e 
		+ i * a * a * f * e 
		- c * c * d * g * e 
		+ a * c * f * g * e,

		c * d * d * h * h 
		- a * d * f * h * h 
		+ i * b * d * d * h 
		+ b * d * f * g * h 
		+ c * g * g * e * e 
		+ i * a * g * e * e 
		- b * f * g * g * e 
		- i * b * d * g * e 
		- i * a * d * h * e 
		- 2 * c * d * g * h * e 
		+ a * f * g * h * e, 

		b * b * f * g * g 
		+ i * b * b * d * g 
		- a * c * d * h * h 
		+ a * a * f * h * h 
		- i * a * b * d * h 
		+ b * c * d * g * h 
		- 2 * a * b * f * g * h 
		- b * c * g * g * e 
		- i * a * b * g * e 
		+ i * a * a * h * e 
		+ a * c * g * h * e, 

		-i * b * b * d * d 
		- b * b * d * f * g 
		- b * c * d * d * h 
		+ a * b * d * f * h 
		- i * a * a * e * e 
		- a * c * g * e * e 
		+ 2 * i * a * b * d * e 
		+ b * c * d * g * e 
			+ a * b * f * g * e 
			+ a * c * d * h * e 
			- a * a * f * h * e
	};
	return (*this) * ((inverseMatrix) / set);
}


dod::Matrix3x3 dod::Matrix3x3::Identity()
{
	return Matrix3x3
	{
		1.0f , 0.0f , 0.0f,
		0.0f , 1.0f , 0.0f,
		0.0f , 0.0f , 1.0f
	};
}

dod::Matrix3x3 dod::Matrix3x3::Inverse() const
{
	float a = matrix[0][0];
	float b = matrix[0][1];
	float c = matrix[0][2];
	float d = matrix[1][0];
	float e = matrix[1][1];
	float f = matrix[1][2];
	float g = matrix[2][0];
	float h = matrix[2][1];
	float i = matrix[2][2];
	float set =
		b * b * d * d +
		b * b * f * f * g * g +
		c * c * d * d * h * h +
		a * a * f * f * h * h -
		2 * a * c * d * f * h * h -
		2 * a * b * f * f * g * h +
		2 * b * c * d * f * g * h +
		a * a * e * e +
		c * c * g * g * e * e -
		2 * a * b * d * e -
		2 * b * c * f * g * g * e -
		2 * c * c * d * g * h * e +
		2 * a * c * f * g * h * e;
	Matrix3x3 inverseMatrix
	{
		a * f * f * h * h
		- c * d * f * h * h
		- i * b * d * f * h
		- b * f * f * g * h
		+ a * e * e
		- i * c * g * e * e
		- b * d * e
		+ i * b * f * g * e
		+ i * c * d * h * e
		+ c * f * g * h * e,

		b * b * d
		- i * b * b * f * g
		+ c * c * d * h * h
		- a * c * f * h * h
		+ i * a * b * f * h
		+ b * c * f * g * h
		- a * b * e
		+ i * b * c * g * e
		- i * a * c * h * e
		- c * c * g * h * e,

		i * b * b * d * f
		+ b * b * f * f * g
		- a * b * f * f * h
		+ b * c * d * f * h
		+ i * a * c * e * e
		+ c * c * g * e * e
		- i * b * c * d * e
		- i * a * b * f * e
		- 2 * b * c * f * g * e
		- c * c * d * h * e
		+ a * c * f * h * e,

		b * d * d
		+ b * f * f * g * g
		- i * c * d * d * h
		+ i * a * d * f * h
		- a * f * f * g * h
		+ c * d * f * g * h
		- a * d * e
		- c * f * g * g * e
		+ i * c * d * g * e
		- i * a * f * g * e,

		-a * b * d
		- b * c * f * g * g
		- i * b * c * d * g
		+ i * a * b * f * g
		+ i * a * c * d * h
		- i * a * a * f * h
		- c * c * d * g * h
		+ a * c * f * g * h
		+ a * a * e
		+ c * c * g * g * e,

		i * b * c * d * d
		- i * a * b * d * f
		- a * b * f * f * g
		+ b * c * d * f * g
		+ c * c * d * d * h
		+ a * a * f * f * h
		- 2 * a * c * d * f * h
		- i * a * c * d * e
		+ i * a * a * f * e
		- c * c * d * g * e
		+ a * c * f * g * e,

		c * d * d * h * h
		- a * d * f * h * h
		+ i * b * d * d * h
		+ b * d * f * g * h
		+ c * g * g * e * e
		+ i * a * g * e * e
		- b * f * g * g * e
		- i * b * d * g * e
		- i * a * d * h * e
		- 2 * c * d * g * h * e
		+ a * f * g * h * e,

		b * b * f * g * g
		+ i * b * b * d * g
		- a * c * d * h * h
		+ a * a * f * h * h
		- i * a * b * d * h
		+ b * c * d * g * h
		- 2 * a * b * f * g * h
		- b * c * g * g * e
		- i * a * b * g * e
		+ i * a * a * h * e
		+ a * c * g * h * e,

		-i * b * b * d * d
		- b * b * d * f * g
		- b * c * d * d * h
		+ a * b * d * f * h
		- i * a * a * e * e
		- a * c * g * e * e
		+ 2 * i * a * b * d * e
		+ b * c * d * g * e
			+ a * b * f * g * e
			+ a * c * d * h * e
			- a * a * f * h * e
	};

	return inverseMatrix;
}
