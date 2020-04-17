// tyrpch: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "Windows.h"
//#define USE_IM_GUI



#if defined(_DEBUG) && defined(x86)
#ifndef USE_IM_GUI
#define USE_IM_GUI
#endif
#endif

#include <SDXLLibrary.h>
#pragma warning(disable : 4091)
#include <SDXLStructs.h>
#include "TyrTypedefs.h"



#define SAFE_DELETE(pointer) {if(pointer) {delete pointer; pointer = nullptr;}}





#endif //PCH_H
