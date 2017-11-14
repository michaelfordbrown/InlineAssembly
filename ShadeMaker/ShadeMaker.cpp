// ShadeMaker.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "CommonHeader.h"
#include "ExecutionTimer.h"

#define IMAGEX 16
#define IMAGEY 3

#define DARK 2
#define LIGHT -1

using namespace std;

void set_image(char image[], size_t xlen, size_t ylen)
{
	for (size_t y = 0; y < ylen; y++)
		for (size_t x = 0; x < xlen; x++)
		{
			image[x + (y * xlen)] = 'a';
		}
}

void print_image(const char image[], size_t xlen, size_t ylen)
{
	for (size_t y = 0; y < ylen; y++)
	{
		for (size_t x = 0; x < xlen; x++)
		{
			cout << image[x + (y * xlen)] << " ";
		}
		cout << endl;
	}
}

void change_image(char image[], size_t xlen, size_t ylen, int factor)
{
	for (size_t y = 0; y < ylen; y++)
		for (size_t x = 0; x < xlen; x++)
		{
			image[x + (y * xlen)] += factor;
		}

	//print_image(image, IMAGEX, IMAGEY);
}

void MMX_change_image(char* image, int xlen, int ylen, char* factor)
{

	_asm
	{

		mov ebx, factor
		movq mm0, QWORD PTR [ebx]

		mov ebx, image
		movq mm1, QWORD PTR[ebx]
		movq mm2, QWORD PTR[ebx + 8]
		movq mm3, QWORD PTR[ebx + 16]
		movq mm4, QWORD PTR[ebx + 24]
		movq mm5, QWORD PTR[ebx + 32]
		movq mm6, QWORD PTR[ebx + 40]

		paddb mm1, mm0;
		paddb mm2, mm0;
		paddb mm3, mm0;
		paddb mm4, mm0;
		paddb mm5, mm0;
		paddb mm6, mm0;

		mov ebx, image
		movq QWORD PTR[ebx], mm1
		movq QWORD PTR[ebx + 8], mm2
		movq QWORD PTR[ebx + 16], mm3
		movq QWORD PTR[ebx + 24], mm4
		movq QWORD PTR[ebx + 32], mm5
		movq QWORD PTR[ebx + 40], mm6
		

		Finished:
		// Exit MMX mode
		emms;
	}

	//print_image(image, IMAGEX, IMAGEY);
	//cout << endl;
}

int main()
{
	cout << "\nShade Maker\n\n";

	ExecutionTimer timer;

	char sample_bitmap[IMAGEX][IMAGEY];

	set_image(sample_bitmap[0], IMAGEX, IMAGEY);

	//print_image(sample_bitmap[0], IMAGEX, IMAGEY);

	string key = "";
	string darker = "+";
	string lighter = "-";
	string stop = "z";
	string start = "a";

	timer.ResetTimer();

	do
	{

//		if (key.compare(darker) == 0)
		{
			change_image(sample_bitmap[0], IMAGEX, IMAGEY, DARK);
		}
		
//		if (key.compare(lighter) == 0)
		{
			change_image(sample_bitmap[0], IMAGEX, IMAGEY, LIGHT);
		}

	} while (sample_bitmap[0] < stop);

	cout << "\nLast Image:\n";
	print_image(sample_bitmap[0], IMAGEX, IMAGEY);
	std::cout << "\nStandard Time for:\t"  << timer.ElapsedTimer() << std::endl;

	cout << "\nUsing MMX To Replace change_image\n";
	set_image(sample_bitmap[0], IMAGEX, IMAGEY);

	//print_image(sample_bitmap[0], IMAGEX, IMAGEY);

	timer.ResetTimer();

	do
	{
		char dark[8] = { 1, 1, 1, 1, 1, 1, 1, 1};

		//		if (key.compare(darker) == 0)
		{
	
			/*
			_asm
			{
				movq mm0, QWORD PTR[dark]

				movq mm1, QWORD PTR[sample_bitmap]
				movq mm2, QWORD PTR[sample_bitmap + 8]
				movq mm3, QWORD PTR[sample_bitmap + 16]
				movq mm4, QWORD PTR[sample_bitmap + 24]
				movq mm5, QWORD PTR[sample_bitmap + 32]
				movq mm6, QWORD PTR[sample_bitmap + 40]
				//movq mm7, QWORD PTR[sample_bitmap + 48]

				paddb mm1, mm0;
				paddb mm2, mm0;
				paddb mm3, mm0;
				paddb mm4, mm0;
				paddb mm5, mm0;
				paddb mm6, mm0;
				//paddb mm7, mm0;

				movq QWORD PTR[sample_bitmap], mm1
				movq QWORD PTR[sample_bitmap + 8], mm2
				movq QWORD PTR[sample_bitmap + 16], mm3
				movq QWORD PTR[sample_bitmap + 24], mm4
				movq QWORD PTR[sample_bitmap + 32], mm5
				movq QWORD PTR[sample_bitmap + 40], mm6
				//movq QWORD PTR[sample_bitmap + 48], mm7
					

					Finished :
				// Exit MMX mode
				emms;
			}
			*/
			MMX_change_image(sample_bitmap[0], IMAGEX, IMAGEY, dark);
		}

		//		if (key.compare(lighter) == 0)
		{
//			change_image(sample_bitmap[0], IMAGEX, IMAGEY, LIGHT);
		}

	} while (sample_bitmap[0] < stop);

	cout << "\nLast Image:\n";
	print_image(sample_bitmap[0], IMAGEX, IMAGEY);
	std::cout << "\nMMX1 Time for:\t" << timer.ElapsedTimer() << std::endl;



	getchar();
    return 0;
}

