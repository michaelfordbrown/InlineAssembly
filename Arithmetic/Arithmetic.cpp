// Arithmetic.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdio.h>

using namespace std;

int AddValues()
{
	/* Add 10 and 20 and store result into register EAX */
	_asm {
		mov eax, 10;
		mov ebx, 20;
		add eax, ebx;
	};
}

int SubtractValues()
{
	/* Subtract 20 from 10 and store result into register EAX */
	_asm {
		mov eax, 10;
		mov ebx, 20;
		sub eax, ebx;
	};
}

int MultiplyValues()
{
	/* Multiply 10 and 20 and store result into register EAX */
	_asm {
		mov eax, 10;
		mov ebx, 20;
		imul eax, ebx;
	};
}

int SetVariable()
{
	int val = 123;

	_asm {
		mov eax, val;
	}
}

int main()
{
	cout << "Arithmetic\n\n";

	cout << "Add Values: " << AddValues() << endl;
	cout << "Subtract Values: " << SubtractValues() << endl;
	cout << "Multiply Values: " << MultiplyValues() << endl;
	cout << "Set Variable: " << SetVariable() << endl;

	getchar();
    return 0;
}

