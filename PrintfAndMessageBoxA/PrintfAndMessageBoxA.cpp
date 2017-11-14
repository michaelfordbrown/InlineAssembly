// PrintfAndMessageBoxA.cpp : Defines the entry point for the console application.
//

/*
 * YouTube: [DEMO] C/C++ Inline Assembly - Printf and MessageBoxA
 *
 * Using the C++ inline assembler to print Hello World and make a message box appear.
 *
 */

#include "stdafx.h"
#include <iostream>
#include <Windows.h>


int main()
{
	// char* is a pointer to the first char in the return "string" (char array). 
	// Although the size of the array isn't given, in C "string"s are null terminated. 
	// Meaning you can start reading the chars of the position the pointer is set to until you encounter a null char
	char * msg = "Hello, World!";

	char * wMsg = "Content of the window . .";

	char * wCaption = "Window title";

	// The __asm keyword invokes the inline assembler and can appear wherever a C or C++ statement is legal. 
	// It cannot appear by itself. It must be followed by an assembly instruction, a group of instructions enclosed 
	// in braces, or, at the very least, an empty pair of braces. The term "__asm block" here refers to any 
	// instruction or group of instructions, whether or not in braces.
	_asm {

/* PRINT message to console
 * EAX is the extended accumulator register (AX) usually used in arithmetic operations */
			mov eax, msg

/*			printf using stack parameter
 *			int printf(
 *				const char *format[,
 *				argument]...
 *			);
 *
 * PUSH, pushes WORD onto the stack (SS:SP) and decrements SP by the size of the operand		
 */
			push eax
			call printf

/* clean up stack */
			pop eax

/*
 * POP UP Message Box
 */
			mov eax, 0
			mov ebx, wCaption
			mov ecx, wMsg
			mov edx, 0

/* MessageBoxA using stack parameters 
 *
 *		int WINAPI MessageBox(
 *			_In_opt_ HWND    hWnd,
 *			_In_opt_ LPCTSTR lpText,
 *			_In_opt_ LPCTSTR lpCaption,
 *			_In_     UINT    uType
 *		);
 */
			push eax
			push ebx
			push ecx
			push edx
			call MessageBoxA

/* clean up stack */
			pop edx
			pop ecx
			pop ebx
			pop eax
		}

	getchar();
    return 0;
}

