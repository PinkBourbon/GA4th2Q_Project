#include "Subset.h"
#include <cmath>

dod::Subset::Subset()
	: sumElement(0), arr3(), diceIndex()
{

}

dod::Subset::~Subset()
{

}

void dod::Subset::Reset()
{
	for (int i = 0; i<3;i++)
	{
		arr3[i] = 0;
		diceIndex[i] = 0;
	}
	sumElement = 0;
}

void dod::Subset::InputSubset(int index, int diceindex, int dicenumber)
{
	arr3[index] = dicenumber;
	diceIndex[index] = diceindex;
}

void dod::Subset::CalcSumElement(int index)
{

		int exponent = arr3[index] - 1;
		int sumNumber = 1;
		for (int j = 0; j<exponent;j++)
		{
			sumNumber *= 6;
		}
		sumElement += sumNumber;
}

void dod::Subset::CreateSubset(int index, int diceindex, int dicenumber)
{
	InputSubset(index, diceindex, dicenumber);
	CalcSumElement(index);
}
