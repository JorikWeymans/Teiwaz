// BubbleBobble.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <vld.h>
#include "BubbleBobble.h"


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE,
	_In_	 LPWSTR,
	_In_	 int)
{


	bub::BubbleBobble game;

	game.Initialize(hInstance);
	game.Run();
	
	
	return 0;
}

