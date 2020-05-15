#pragma once

#ifndef STDAFX_H
#define STDAFX_H
#include "Windows.h"
#include <SDXLLibrary.h>
#pragma warning(disable : 4091)
#include <SDXLStructs.h>
#include <TyrTypedefs.h>
#if defined(_DEBUG) && defined(x86)
#ifndef EDITOR_MODE
#define EDITOR_MODE
#endif
#endif
#endif 


