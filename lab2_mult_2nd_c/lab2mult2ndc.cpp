// lab2mult2ndc.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "LI.h"
#include <iostream>
#include <random>
#include <cmath>
using namespace std;

int main()
{

	LI a="17";
	LI b = "8";
	cout << boolalpha << a.Rabin_Miller() << endl;;
	
	//LI(a*b).out();
	//b.out();

/*	std::random_device random_device; // �������� ��������.
	std::mt19937 generator(random_device()); // ��������� ��������� �����.
											 // (����� ������� ���� ���������������� ��������, ����� ����� ������)

	std::uniform_int_distribution<> distribution(2, 51); // ����������� ������������� [10, 20]
	for (int i = 0; i < 40; ++i) {
		int x = distribution(generator); // ��������� �����.
		std::cout << x << '\n';

	}
	
	*/

	




	system("pause");
    return 0;
}

