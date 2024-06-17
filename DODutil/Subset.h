#pragma once
namespace dod
{
	struct Subset
	{
		Subset();
		~Subset();

	public:
		void Reset();													// 0으로 밀어주기
		void InputSubset(int index, int diceindex, int dicenumber);		// 부분집합 입력하기
		void CalcSumElement(int index);											// 6진수 변환 합 구하기
		void CreateSubset(int index, int diceindex, int dicenumber);	// 입력과 합 계산을 순서대로 실행하는 묶음

	public:
		int sumElement;		// 3~5개 원소의 6진수 합
		int arr3[5];		// 3개 원소
		int diceIndex[5];	// 각 원소의 _diceNumber 내의 인덱스
	};
}

