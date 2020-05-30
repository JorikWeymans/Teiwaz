// tyrpch: This is a precompiled header file.
// Files listed below are compiled only once, improving build performance for future builds.
// This also affects IntelliSense performance, including code completion and many code browsing features.
// However, files listed here are ALL re-compiled if any one of them is updated between builds.
// Do not add files here that you will be updating frequently as this negates the performance advantage.

#ifndef PCH_H
#define PCH_H

// add headers that you want to pre-compile here
#include "Windows.h"
//#define EDITOR_MODE



#if defined(_DEBUG) && defined(x86)
#ifndef EDITOR_MODE
#define EDITOR_MODE
#endif
#endif

#include <SDXLLibrary.h>
#pragma warning(disable : 4091)
#include <SDXLStructs.h>

#define ARRAY_SIZE(array)          (static_cast<int>(sizeof(array) / sizeof(*array)))   

//https://github.com/Neargye/magic_enum Unity has enum.ToString(), this hpp gives the same functionality and other stuff as well
#define MAGIC_ENUM_RANGE_MIN 0
#define MAGIC_ENUM_RANGE_MAX 20
#include <magic_enum.hpp>
#include "TyrTypedefs.h"
#include "TyrFunctions.h"
#include "TyrEnums.h"
#define SAFE_DELETE(pointer) {if(pointer) {delete pointer; pointer = nullptr;}}





#endif //PCH_H
