#pragma once
namespace dod
{
	struct Subset
	{
		Subset();
		~Subset();

	public:
		void Reset();													// 0���� �о��ֱ�
		void InputSubset(int index, int diceindex, int dicenumber);		// �κ����� �Է��ϱ�
		void CalcSumElement(int index);											// 6���� ��ȯ �� ���ϱ�
		void CreateSubset(int index, int diceindex, int dicenumber);	// �Է°� �� ����� ������� �����ϴ� ����

	public:
		int sumElement;		// 3~5�� ������ 6���� ��
		int arr3[5];		// 3�� ����
		int diceIndex[5];	// �� ������ _diceNumber ���� �ε���
	};
}

