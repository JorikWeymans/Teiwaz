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

SDXLLibrary_API HRESULT SDXL_Present();

SDXLLibrary_API SDXL::SDXLVec2 SDXL_GetImageDimensions(SDXL::SDXLImage* pImage);