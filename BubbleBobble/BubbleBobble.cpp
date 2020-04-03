// BubbleBobble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <Windows.h>
#include <Teiwazlib.h>
#include <TeiwazEngine.h>
#include <vld.h>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE,
	_In_	 LPWSTR,
	_In_	 int)
{


	tyr::TeiwazEngine engine;

	engine.Initialize(hInstance);
	engine.Run();
	
	
	return 0;
}
