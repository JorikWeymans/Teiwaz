#pragma once

#ifndef STDAFX_H
#define STDAFX_H
#include "Windows.h"
#include <SDXLLibrary.h>
#pragma warning(disable : 4091)
#include <SDXLStructs.h>
#include <TyrTypedefs.h>
#if defined(_DEBUG) && defined(x86)
#ifndef USE_IM_GUI
#define USE_IM_GUI
#endif
#endif
#endif 


