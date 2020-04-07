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


	struct float2
	{
		float2(): x(0.f), y(0.f){}
		explicit float2(float _x, float _y) : x(_x), y(_y) {}
		float x, y;
	};
	
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

// ****** ------------------ ******
// *  ___ _  _ _   _ __  __ ___   *
// * | __| \| | | | |  \/  / __|  *
// * | _|| .` | |_| | |\/| \__ \  *
// * |___|_|\_|\___/|_|  |_|___/  *
// *							  *
// ****** ------------------- *****
// 
enum class SDXL_ImGuiDir : int
{
	ImGuiDir_None = -1,
	ImGuiDir_Left = 0,
	ImGuiDir_Right = 1,
	ImGuiDir_Up = 2,
	ImGuiDir_Down = 3,
	ImGuiDir_COUNT
};

/*
 * 
                             

 */
// ****** ------------------------------------ ******
// *  ___ _   _ _  _  ___ _____ ___ ___  _  _ ___ 	*
// * | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|	*
// * | _|| |_| | .` | (__  | |  | | (_) | .` \__ \	*
// * |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/	*
// *                                             	*
// ****** ------------------------------------ ******
SDXLLibrary_API void SDXL_IMGUI_Test();
SDXLLibrary_API void SDXL_ImGui_NewFrame();
SDXLLibrary_API void SDXL_ImGui_Begin(const char* name);
SDXLLibrary_API void SDXL_ImGui_End();

// *** ------------------------- ***
// *  __        __   __   __   __  *   
// * /  ` |  | |__) /__` /  \ |__) *   
// * \__, \__/ |  \ .__/ \__/ |  \ *
// *                               *
// *** ------------------------- ***

// - By "cursor" we mean the current output position.
// - The typical widget behavior is to output themselves at the current cursor position, then move the cursor one line down.
// - You can call SameLine() between widgets to undo the last carriage return and output at the right of the preceeding widget.
// - Attention! We currently have inconsistencies between window-local and absolute positions we will aim to fix with future API:
//    Window-local coordinates:   SameLine(), GetCursorPos(), SetCursorPos(), GetCursorStartPos(), GetContentRegionMax(), GetWindowContentRegion*(), PushTextWrapPos()
//    Absolute coordinate:        GetCursorScreenPos(), SetCursorScreenPos(), all ImDrawList:: functions.
SDXLLibrary_API void   SDXL_ImGui_Separator();                                                    // separator, generally horizontal. inside a menu bar or in horizontal layout mode, this becomes a vertical separator.
SDXLLibrary_API void   SDXL_ImGui_SameLine(float offset_from_start_x = 0.0f, float spacing = -1.0f);  // call between widgets or groups to layout them horizontally. X position given in window coordinates.
SDXLLibrary_API void   SDXL_ImGui_NewLine();                                                      // undo a SameLine() or force a new line when in an horizontal-layout context.
SDXLLibrary_API void   SDXL_ImGui_Spacing();                                                      // add vertical spacing.
SDXLLibrary_API void   SDXL_ImGui_Dummy(const SDXL::float2& size);                                // add a dummy item of given size. unlike InvisibleButton(), Dummy() won't take the mouse click or be navigable into.
SDXLLibrary_API void   SDXL_ImGui_Indent(float indent_w = 0.0f);                                  // move content position toward the right, by style.IndentSpacing or indent_w if != 0
SDXLLibrary_API void   SDXL_ImGui_Unindent(float indent_w = 0.0f);                                // move content position back to the left, by style.IndentSpacing or indent_w if != 0
SDXLLibrary_API void   SDXL_ImGui_BeginGroup();                                                   // lock horizontal starting position
SDXLLibrary_API void   SDXL_ImGui_EndGroup();                                                     // unlock horizontal starting position + capture the whole group bounding box into one "item" (so you can use IsItemHovered() or layout primitives such as SameLine() on whole group, etc.)
SDXLLibrary_API SDXL::float2 SDXL_ImGui_GetCursorPos();                                           // cursor position in window coordinates (relative to window position)
SDXLLibrary_API float  SDXL_ImGui_GetCursorPosX();                                                //   (some functions are using window-relative coordinates, such as: GetCursorPos, GetCursorStartPos, GetContentRegionMax, GetWindowContentRegion* etc.
SDXLLibrary_API float  SDXL_ImGui_GetCursorPosY();                                                //    other functions such as GetCursorScreenPos or everything in ImDrawList::
SDXLLibrary_API void   SDXL_ImGui_SetCursorPos(const SDXL::float2& local_pos);                    //    are using the main, absolute coordinate system.
SDXLLibrary_API void   SDXL_ImGui_SetCursorPosX(float local_x);                                   //    GetWindowPos() + GetCursorPos() == GetCursorScreenPos() etc.)
SDXLLibrary_API void   SDXL_ImGui_SetCursorPosY(float local_y);                                   //
SDXLLibrary_API SDXL::float2 SDXL_ImGui_GetCursorStartPos();                                      // initial cursor position in window coordinates
SDXLLibrary_API SDXL::float2 SDXL_ImGui_GetCursorScreenPos();                                     // cursor position in absolute screen coordinates [0..io.DisplaySize] (useful to work with ImDrawList API)
SDXLLibrary_API void   SDXL_ImGui_SetCursorScreenPos(const SDXL::float2& pos);                    // cursor position in absolute screen coordinates [0..io.DisplaySize]
SDXLLibrary_API void   SDXL_ImGui_AlignTextToFramePadding();                                      // vertically align upcoming text baseline to FramePadding.y so that it will align properly to regularly framed items (call if you have text on a line before a framed item)
SDXLLibrary_API float  SDXL_ImGui_GetTextLineHeight();                                            // ~ FontSize
SDXLLibrary_API float  SDXL_ImGui_GetTextLineHeightWithSpacing();                                 // ~ FontSize + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of text)
SDXLLibrary_API float  SDXL_ImGui_GetFrameHeight();                                               // ~ FontSize + style.FramePadding.y * 2
SDXLLibrary_API float  SDXL_ImGui_GetFrameHeightWithSpacing();                                    // ~ FontSize + style.FramePadding.y * 2 + style.ItemSpacing.y (distance in pixels between 2 consecutive lines of framed widgets)


// *** ---------------------- ***
// * _ _ _ _ ___  ____ ____ ___ *
// * | | | | |  \ | __ |___  |  *
// * |_|_| | |__/ |__] |___  |  *
// *							*
// *** ---------------------- ***


// **---------------**
// * ----- Main -----*
// **---------------**
// - Most widgets return true when the value has been changed or when pressed/selected
// - You may also use one of the many IsItemXXX functions (e.g. IsItemActive, IsItemHovered, etc.) to query widget state.
SDXLLibrary_API bool SDXL_ImGui_Button(const char* label, const SDXL::float2& size = SDXL::float2(0.f, 0.f));    // button
SDXLLibrary_API bool SDXL_ImGui_SmallButton(const char* label);															// button with FramePadding=(0,0) to easily embed within text
SDXLLibrary_API bool SDXL_ImGui_InvisibleButton(const char* str_id, const SDXL::float2& size);        // button behavior without the visuals, frequently useful to build custom behaviors using the public api (along with IsItemActive, IsItemHovered, etc.)
SDXLLibrary_API bool SDXL_ImGui_ArrowButton(const char* str_id, SDXL_ImGuiDir dir);                  // square button with an arrow shape
SDXLLibrary_API bool SDXL_ImGui_Checkbox(const char* label, bool* v);
SDXLLibrary_API bool SDXL_ImGui_CheckboxFlags(const char* label, unsigned int* flags, unsigned int flags_value);
SDXLLibrary_API bool SDXL_ImGui_RadioButton(const char* label, bool active);                    // use with e.g. if (RadioButton("one", my_value==1)) { my_value = 1; }
SDXLLibrary_API bool SDXL_ImGui_RadioButton(const char* label, int* v, int v_button);           // shortcut to handle the above pattern when value is an integer
SDXLLibrary_API void SDXL_ImGui_ProgressBar(float fraction, const SDXL::float2& size_arg = SDXL::float2(-1, 0), const char* overlay = nullptr);
SDXLLibrary_API void SDXL_ImGui_Bullet();                                                       // draw a small circle and keep the cursor on the same line. advance cursor x position by GetTreeNodeToLabelSpacing(), same distance that TreeNode() uses

// **---------------**
// * ----- Drag -----*
// **---------------**
// - CTRL+Click on any drag box to turn them into an input box. Manually input values aren't clamped and can go off-bounds.
// - For all the Float2/Float3/Float4/Int2/Int3/Int4 versions of every functions, note that a 'float v[X]' function argument is the same as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible. You can pass address of your first element out of a contiguous set, e.g. &myvector.x
// - Adjust format string to decorate the value with a prefix, a suffix, or adapt the editing and display precision e.g. "%.3f" -> 1.234; "%5.2f secs" -> 01.23 secs; "Biscuit: %.0f" -> Biscuit: 1; etc.
// - Speed are per-pixel of mouse movement (v_speed=0.2f: mouse needs to move by 5 pixels to increase value by 1). For gamepad/keyboard navigation, minimum speed is Max(v_speed, minimum_step_at_given_precision).
// - Use v_min < v_max to clamp edits to given limits. Note that CTRL+Click manual input can override those limits.
// - Use v_max = FLT_MAX / INT_MAX etc to avoid clamping to a maximum, same with v_min = -FLT_MAX / INT_MIN to avoid clamping to a minimum.
// - Use v_min > v_max to lock edits.
SDXLLibrary_API bool SDXL_ImGui_DragFloat(const char* label, float* v, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);     // If v_min >= v_max we have no bound
SDXLLibrary_API bool SDXL_ImGui_DragFloat2(const char* label, float v[2], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_DragFloat3(const char* label, float v[3], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_DragFloat4(const char* label, float v[4], float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_DragFloatRange2(const char* label, float* v_current_min, float* v_current_max, float v_speed = 1.0f, float v_min = 0.0f, float v_max = 0.0f, const char* format = "%.3f", const char* format_max = NULL, float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_DragInt(const char* label, int* v, float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");                                       // If v_min >= v_max we have no bound
SDXLLibrary_API bool SDXL_ImGui_DragInt2(const char* label, int v[2], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
SDXLLibrary_API bool SDXL_ImGui_DragInt3(const char* label, int v[3], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");
SDXLLibrary_API bool SDXL_ImGui_DragInt4(const char* label, int v[4], float v_speed = 1.0f, int v_min = 0, int v_max = 0, const char* format = "%d");

// **---------------**
// * ---- Slider ----*
// **---------------**
// - CTRL+Click on any slider to turn them into an input box. Manually input values aren't clamped and can go off-bounds.
// - Adjust format string to decorate the value with a prefix, a suffix, or adapt the editing and display precision e.g. "%.3f" -> 1.234; "%5.2f secs" -> 01.23 secs; "Biscuit: %.0f" -> Biscuit: 1; etc.
SDXLLibrary_API bool SDXL_ImGui_SliderFloat(const char* label, float* v, float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);     // adjust format to decorate the value with a prefix or a suffix for in-slider labels or unit display. Use power!=1.0 for power curve sliders
SDXLLibrary_API bool SDXL_ImGui_SliderFloat2(const char* label, float v[2], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_SliderFloat3(const char* label, float v[3], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_SliderFloat4(const char* label, float v[4], float v_min, float v_max, const char* format = "%.3f", float power = 1.0f);
SDXLLibrary_API bool SDXL_ImGui_SliderAngle(const char* label, float* v_rad, float v_degrees_min = -360.0f, float v_degrees_max = +360.0f, const char* format = "%.0f deg");
SDXLLibrary_API bool SDXL_ImGui_SliderInt(const char* label, int* v, int v_min, int v_max, const char* format = "%d");
SDXLLibrary_API bool SDXL_ImGui_SliderInt2(const char* label, int v[2], int v_min, int v_max, const char* format = "%d");
SDXLLibrary_API bool SDXL_ImGui_SliderInt3(const char* label, int v[3], int v_min, int v_max, const char* format = "%d");
SDXLLibrary_API bool SDXL_ImGui_SliderInt4(const char* label, int v[4], int v_min, int v_max, const char* format = "%d");

// **---------------**
// * ---- Slider ----*
// **---------------**
SDXLLibrary_API bool SDXL_ImGui_InputText(const char* label, char* buf, size_t buf_size,void* user_data = nullptr);
SDXLLibrary_API bool SDXL_ImGui_InputTextMultiline(const char* label, char* buf, size_t buf_size, const SDXL::float2& size = SDXL::float2(0.f,0.f) , void* user_data = nullptr);



// **---------------**
// * ---- Colors ----*
// **---------------**
// Widgets: Color Editor/Picker (tip: the ColorEdit* functions have a little colored preview square that can be left-clicked to open a picker, and right-clicked to open an option menu.)
// - Note that in C++ a 'float v[X]' function argument is the _same_ as 'float* v', the array syntax is just a way to document the number of elements that are expected to be accessible.
// - You can pass the address of a first float element out of a contiguous structure, e.g. &myvector.x
SDXLLibrary_API bool  SDXL_ImGui_ColorEdit3(const char* label, float col[3]);
SDXLLibrary_API bool  SDXL_ImGui_ColorEdit4(const char* label, float col[4]);
SDXLLibrary_API bool  SDXL_ImGui_ColorPicker3(const char* label, float col[3]);
SDXLLibrary_API bool  SDXL_ImGui_ColorPicker4(const char* label, float col[4], const float* ref_col = nullptr);
//SDXLLibrary_API bool ColorButton(const char* desc_id, const ImVec4& col, ImGuiColorEditFlags flags = 0, ImVec2 size = ImVec2(0, 0));  // display a colored square/button, hover for details, return true when pressed.
//SDXLLibrary_API bool SetColorEditOptions(ImGuiColorEditFlags flags);                     // initialize current options (generally on application startup) if you want to select a default format, picker type, etc. User will be able to change many settings, unless you pass the _NoOptions flag to your calls.











#endif