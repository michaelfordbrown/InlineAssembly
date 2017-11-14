// GettingIntox64ASMFromC++.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include<conio.h>

using namespace std;

int GetValuefromASMInline()
{
	_asm {
		mov eax, 39
	}
}

int main()
{
	cout << "ASM said " << GetValuefromASMInline() << endl;

	getchar();
    return 0;
}

