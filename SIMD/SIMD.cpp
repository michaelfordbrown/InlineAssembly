// SIMD.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <string>

using namespace std;

string get_cpu_name()
{
	// unsigned integer type with width of exactly 32 bits.
	uint32_t data[4] = { 0 };

	_asm
	{
		cpuid;
		mov data[0], ebx;
		mov data[4], edx;
		mov data[8], ecx;
	}

	return string((const char*)data);
}

void display_farray(float a[])
{
	for (size_t i = 0; i < 4; i++)
	{
		cout << a[i] << "\t";
	}
	cout << endl;
}

void display_iarray(int a[])
{
	for (size_t i = 0; i < 4; i++)
	{
		cout << a[i] << "\t";
	}
	cout << endl;
}

void assembler()
{
	cout << "CPU is " << get_cpu_name() << endl;

	float f1[] = { 1.f, 2.f, 3.f, 4.f };
	float f2[] = { 5.f, 4.f, 3.f, 2.f };
	float fresult[4] = { 0.f };
	
	cout << "SSE (floating point) Using 128 Bit Wide Registers\n\n";

	_asm
	{
		movups xmm1, f1;
		movups xmm2, f2;
		mulps xmm1, xmm2;
		movups fresult, xmm1;
	}

	display_farray(f1);
	display_farray(f2);
	cout << endl;
	display_farray(fresult);
}

void display_carrary(char a[], int l)
{
	for (int i = 0; i < l; i++)
	{
		cout << (int)a[i] << "  ";
	}
}

#define ASIZE 16

void MMXCopy(char* source, char* destination, int byteCount)
{

	unsigned char t[16] = { 1, 2, 3, 4, 5,6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	_asm
	{
		mov ecx, byteCount
		cmp ecx, 16;
		jnz Finished

		mov ebx, source
		movq mm0, QWORD PTR[ebx]
		movq mm1, QWORD PTR[ebx + 8]

		mov ebx, destination
		movq QWORD PTR[ebx], mm0
		movq QWORD PTR[ebx +8], mm1

	Finished:
		// Exit MMX mode
		mov byteCount, ecx
		emms;
	}
}



void mmx_example()
{
	char a[ASIZE] = { 0 };
	char b[ASIZE] = { 1, 2, 3, 4, 5,6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	unsigned char c[ASIZE] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };

	cout << "Original values:\n";
	display_carrary(b, ASIZE);
	
	MMXCopy(a, b, ASIZE);

	cout << "\nNew values:\n";
	display_carrary(b, ASIZE);

	cout << "\n\n\n";
}

int main()
{
	//assembler();

	mmx_example();

	getchar();
    return 0;
}

