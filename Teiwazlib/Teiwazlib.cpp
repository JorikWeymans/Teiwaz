// Teiwazlib.cpp : Defines the functions for the static library.
//

#include "pch.h"
#include "Teiwazlib.h"
#include "Windows.h"
#include <SDXLLibrary.h>
// TODO: This is an example of a library function
void Test(HINSTANCE hInstance)
{
	SDXL_Init(hInstance, "Teiwazlib", 1280, 720);
	//Test
}
