#pragma once

#ifdef SDXLLibrary_EXPORTS
#define SDXLLibrary_API __declspec(dllexport)
#else
#define SDXLLibrary_API __declspec(dllimport)
#endif

#include <string>

// -- Header files includes to expose them
namespace SDXL
{
	struct SDXLVec4;
	struct SDXL_EVENT;
	class SDXLImage;
	class SDXLFont;
	class PostProcessingEffect;
	struct SDXLVec2;
	struct SDXLRect;
	
}

struct ID3D11Device;
struct ID3D11DeviceContext;
// --

SDXLLibrary_API HRESULT SDXL_Init(HINSTANCE hInstance, const std::string& windowTitle,  int width, int height);
SDXLLibrary_API HRESULT SDXL_InitRenderers( const std::wstring& imageEffectFile, 
											const std::wstring& textEffectFile,
											const std::wstring& debugEffectFile);
SDXLLibrary_API HRESULT SDXL_PollEvent(SDXL::SDXL_EVENT & event);
SDXLLibrary_API const char* SDXL_GetError();

///**-------------------------------------**
///*---------- CREATE FUNCTIONS -----------*
///**-------------------------------------**
SDXLLibrary_API HRESULT SDXL_CreateImage(SDXL::SDXLImage **image, const std::wstring & path);
SDXLLibrary_API HRESULT SDXL_CreateFont(SDXL::SDXLFont **font, const std::wstring & path);

///**-------------------------------------**
///*---------- DESTROY FUNCTIONS ----------*
///**-------------------------------------**
SDXLLibrary_API void SDXL_DestroyImage(SDXL::SDXLImage **image);
SDXLLibrary_API void SDXL_DestroyFont(SDXL::SDXLFont** font);
SDXLLibrary_API void SDXL_Destroy();
/// <summary> Adds PPE to the renderer, using the renderer index.
/// <para> The renderer takes control of the PPE pointer</para>
/// </summary>
SDXLLibrary_API HRESULT SDXL_AddPostProcessingEffect(SDXL::PostProcessingEffect *pPost);
SDXLLibrary_API HRESULT SDXL_RemovePostProcessingEffect(SDXL::PostProcessingEffect *pPost);



///**-------------------------------------**
///*---------- RENDER FUNCTIONS -----------*
///**-------------------------------------**
SDXLLibrary_API void SDXL_Clear();

SDXLLibrary_API void SDXL_RenderImage(SDXL::SDXLImage * pImage, const SDXL::SDXLVec2 & pos, const SDXL::SDXLVec2 & pivot, const SDXL::SDXLVec2 & scale, float rot = 0.f, float depth = 0.f);
SDXLLibrary_API void SDXL_RenderImage(SDXL::SDXLImage * pImage, const SDXL::SDXLVec2 & pos, const SDXL::SDXLVec2 & pivot, const SDXL::SDXLVec2 & scale, const SDXL::SDXLRect& srcRect, float rot = 0.f, float depth = 0.f);
SDXLLibrary_API void SDXL_RenderText(SDXL::SDXLFont * pFont, const std::wstring & text, const SDXL::SDXLVec2& pos, const SDXL::SDXLVec4& color);
SDXLLibrary_API void SDXL_RenderDebugLine(const SDXL::SDXLVec2& start, const SDXL::SDXLVec2& end, const SDXL::SDXLVec4& color);

SDXLLibrary_API HRESULT SDXL_RenderAll();
SDXLLibrary_API HRESULT SDXL_Present();


SDXLLibrary_API SDXL::SDXLVec2 SDXL_GetImageDimensions(SDXL::SDXLImage* pImage);
SDXLLibrary_API ID3D11Device* SDXL_GetID3D11Device();
SDXLLibrary_API ID3D11DeviceContext* SDXL_GetID3D11DeviceContext();
SDXLLibrary_API HWND SDXL_GetWindowHandle();


// ***** ------------------------------------------------------------------------------------- *****
// *																							   *
// *  _____             _____  _   _  _____   _    _                                               *
// * |_   _|           |  __ \| | | ||_   _| | |  | |                                              *
// *   | |   _ __ ___  | |  \/| | | |  | |   | |  | | _ __   __ _  _ __   _ __    ___  _ __  ___   *
// *   | |  | '_ ` _ \ | | __ | | | |  | |   | |/\| || '__| / _` || '_ \ | '_ \  / _ \| '__|/ __|  *
// *  _| |_ | | | | | || |_\ \| |_| | _| |_  \  /\  /| |   | (_| || |_) || |_) ||  __/| |   \__ \  *
// *  \___/ |_| |_| |_| \____/ \___/  \___/   \/  \/ |_|    \__,_|| .__/ | .__/  \___||_|   |___/  *
// *                                                              | |    | |                       *
// *                                                              |_|    |_|                       *
// * 																							   *
// ***** ------------------------------------------------------------------------------------- *****

#if defined(_DEBUG) && defined(x86)
#define USE_IM_GUI
#endif

#ifdef USE_IM_GUI
SDXLLibrary_API void SDXL_IMGUI_Test();
SDXLLibrary_API void SDXL_ImGui_NewFrame();
SDXLLibrary_API void SDXL_ImGui_Begin(const char* name);
SDXLLibrary_API void SDXL_ImGui_End();

///**-------------------------------------**
///*--------------- DragX -----------------*
///**-------------------------------------**
SDXLLibrary_API bool SDXL_ImGui_DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);     // If v_min >= v_max we have no bound
SDXLLibrary_API bool SDXL_ImGui_DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = NULL, float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");                                       // If v_min >= v_max we have no bound
SDXLLibrary_API bool SDXL_ImGui_DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
SDXLLibrary_API bool SDXL_ImGui_DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
SDXLLibrary_API bool SDXL_ImGui_DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
#endif