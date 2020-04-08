#pragma once

#ifdef SDXLLibrary_EXPORTS
#define SDXLLibrary_API __declspec(dllexport)
#else
#define SDXLLibrary_API __declspec(dllimport)
#endif

#include <string>

// -- Header files includes to expose them
struct ImVec2;

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
		explicit operator ImVec2() const;
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
typedef unsigned int SDXL_ImGUiID;

enum class SDXL_ImGuiDir : int
{
	ImGuiDir_None = -1,
	ImGuiDir_Left = 0,
	ImGuiDir_Right = 1,
	ImGuiDir_Up = 2,
	ImGuiDir_Down = 3,
	ImGuiDir_COUNT
};

enum class SDXL_ImGuiSelectableFlags : int
{
	None = 0,
	DontClosePopups = 1 << 0,   // Clicking this don't close parent popup window
	SpanAllColumns = 1 << 1,   // Selectable frame can span all columns (text will still fit in current column)
	AllowDoubleClick = 1 << 2,   // Generate press events on double clicks too
	Disabled = 1 << 3,   // Cannot be selected, display grayed out text
	AllowItemOverlap = 1 << 4    // (WIP) Hit testing to allow subsequent widgets to overlap this one
};

enum class SDXL_ImGuiWindowFlags : int
{
	None = 0,
	NoTitleBar = 1 << 0,   // Disable title-bar
	NoResize = 1 << 1,   // Disable user resizing with the lower-right grip
	NoMove = 1 << 2,   // Disable user moving the window
	NoScrollbar = 1 << 3,   // Disable scrollbars (window can still scroll with mouse or programmatically)
	NoScrollWithMouse = 1 << 4,   // Disable user vertically scrolling with mouse wheel. On child window, mouse wheel will be forwarded to the parent unless NoScrollbar is also set.
	NoCollapse = 1 << 5,   // Disable user collapsing window by double-clicking on it
	AlwaysAutoResize = 1 << 6,   // Resize every window to its content every frame
	NoBackground = 1 << 7,   // Disable drawing background color (WindowBg, etc.) and outside border. Similar as using SetNextWindowBgAlpha(0.0f).
	NoSavedSettings = 1 << 8,   // Never load/save settings in .ini file
	NoMouseInputs = 1 << 9,   // Disable catching mouse, hovering test with pass through.
	MenuBar = 1 << 10,  // Has a menu-bar
	HorizontalScrollbar = 1 << 11,  // Allow horizontal scrollbar to appear (off by default). You may use SetNextWindowContentSize(ImVec2(width,0.0f)); prior to calling Begin() to specify width. Read code in imgui_demo in the "Horizontal Scrolling" section.
	NoFocusOnAppearing = 1 << 12,  // Disable taking focus when transitioning from hidden to visible state
	NoBringToFrontOnFocus = 1 << 13,  // Disable bringing window to front when taking focus (e.g. clicking on it or programmatically giving it focus)
	AlwaysVerticalScrollbar = 1 << 14,  // Always show vertical scrollbar (even if ContentSize.y < Size.y)
	AlwaysHorizontalScrollbar = 1 << 15,  // Always show horizontal scrollbar (even if ContentSize.x < Size.x)
	AlwaysUseWindowPadding = 1 << 16,  // Ensure child windows without border uses style.WindowPadding (ignored by default for non-bordered child windows, because more convenient)
	NoNavInputs = 1 << 18,  // No gamepad/keyboard navigation within the window
	NoNavFocus = 1 << 19,  // No focusing toward this window with gamepad/keyboard navigation (e.g. skipped by CTRL+TAB)
	UnsavedDocument = 1 << 20,  // Append '*' to title without affecting the ID, as a convenience to avoid using the ### operator. When used in a tab/docking context, tab is selected on closure and closure is deferred by one frame to allow code to cancel the closure (with a confirmation popup, etc.) without flicker.
	NoNav = NoNavInputs | NoNavFocus,
	NoDecoration = NoTitleBar | NoResize | NoScrollbar | NoCollapse,
	NoInputs = NoMouseInputs | NoNavInputs | NoNavFocus,

	// [Internal]
	NavFlattened = 1 << 23,  // [BETA] Allow gamepad/keyboard navigation to cross over parent border to this child (only use on child that have no scrolling!)
	ChildWindow = 1 << 24,  // Don't use! For internal use by BeginChild()
	Tooltip = 1 << 25,  // Don't use! For internal use by BeginTooltip()
	Popup = 1 << 26,  // Don't use! For internal use by BeginPopup()
	Modal = 1 << 27,  // Don't use! For internal use by BeginPopupModal()
	ChildMenu = 1 << 28   // Don't use! For internal use by BeginMenu()
};

enum class SDXL_ImGuiFocusedFlags
{
	None = 0,
	ChildWindows = 1 << 0,   // IsWindowFocused(): Return true if any children of the window is focused
	RootWindow = 1 << 1,   // IsWindowFocused(): Test from root window (top most parent of the current hierarchy)
	AnyWindow = 1 << 2,   // IsWindowFocused(): Return true if any window is focused. Important: If you are trying to tell how to dispatch your low-level inputs, do NOT use this. Use 'io.WantCaptureMouse' instead! Please read the FAQ!
	RootAndChildWindows = RootWindow | ChildWindows
};

enum class SDXL_ImGuiCond : int
{
	Always = 1 << 0,   // Set the variable
	Once = 1 << 1,   // Set the variable once per runtime session (only the first call with succeed)
	FirstUseEver = 1 << 2,   // Set the variable if the object/window has no persistently saved data (no entry in .ini file)
	Appearing = 1 << 3    // Set the variable if the object/window is appearing after being hidden/inactive (or the first time)
};

// ****** ------------------------------------ ******
// *  ___ _   _ _  _  ___ _____ ___ ___  _  _ ___ 	*
// * | __| | | | \| |/ __|_   _|_ _/ _ \| \| / __|	*
// * | _|| |_| | .` | (__  | |  | | (_) | .` \__ \	*
// * |_|  \___/|_|\_|\___| |_| |___\___/|_|\_|___/	*
// *                                             	*
// ****** ------------------------------------ ******

// *** ------------------------ ***
// * _ _ _ _ _  _ ___  ____ _ _ _ *
// * | | | | |\ | |  \ |  | | | | *
// * |_|_| | | \| |__/ |__| |_|_| *
// *                              *
// *** ------------------------ ***

// **---------------**
// * ----- Base ---- *
// **---------------**
SDXLLibrary_API void SDXL_ImGui_NewFrame();
SDXLLibrary_API void SDXL_ImGui_Begin(const char* name, bool* p_open = nullptr, SDXL_ImGuiWindowFlags flags = SDXL_ImGuiWindowFlags::None);
SDXLLibrary_API void SDXL_ImGui_End();

// **---------------**
// * ---- Childs --- *
// **---------------**
SDXLLibrary_API bool SDXL_ImGui_BeginChild(const char* str_id, const SDXL::float2& size = SDXL::float2(0, 0), bool border = false, SDXL_ImGuiWindowFlags flags = SDXL_ImGuiWindowFlags::None);
SDXLLibrary_API bool SDXL_ImGui_BeginChild(SDXL_ImGUiID id, const SDXL::float2& size = SDXL::float2(0, 0), bool border = false, SDXL_ImGuiWindowFlags flags = SDXL_ImGuiWindowFlags::None);
SDXLLibrary_API void SDXL_ImGui_EndChild();

// **---------------**
// * -- Utilities -- *
// **---------------**
SDXLLibrary_API bool SDXL_ImGui_IsWindowAppearing();
SDXLLibrary_API bool SDXL_ImGui_IsWindowCollapsed();
SDXLLibrary_API bool SDXL_ImGui_IsWindowFocused(SDXL_ImGuiFocusedFlags flags = SDXL_ImGuiFocusedFlags::None); // is current window focused? or its root/child, depending on flags. see flags for options.
SDXLLibrary_API bool SDXL_ImGui_IsWindowHovered(SDXL_ImGuiFocusedFlags flags = SDXL_ImGuiFocusedFlags::None); // is current window hovered (and typically: not blocked by a popup/modal)? see flags for options. NB: If you are trying to check whether your mouse should be dispatched to imgui or to your app, you should use the 'io.WantCaptureMouse' boolean for that! Please read the FAQ!
SDXLLibrary_API SDXL::float2 SDXL_ImGui_GetWindowPos();                                                       // get current window position in screen space (useful if you want to do your own drawing via the DrawList API)
SDXLLibrary_API SDXL::float2 SDXL_ImGui_GetWindowSize();                                                      // get current window size
SDXLLibrary_API float SDXL_ImGui_GetWindowWidth();                                                            // get current window width (shortcut for GetWindowSize().x)
SDXLLibrary_API float SDXL_ImGui_GetWindowHeight();                                                           // get current window height (shortcut for GetWindowSize().y)

SDXLLibrary_API void SDXL_ImGui_SetNextWindowPos(const SDXL::float2& pos, SDXL_ImGuiCond cond = SDXL_ImGuiCond::Always, const SDXL::float2& pivot = SDXL::float2(0.f, 0.f)); // set next window position. call before Begin(). use pivot=(0.5f,0.5f) to center on given point, etc.
SDXLLibrary_API void SDXL_ImGui_SetNextWindowSize(const SDXL::float2& size, SDXL_ImGuiCond cond = SDXL_ImGuiCond::Always);                  // set next window size. set axis to SDXL_ImGuiCond::Always.0f to force an auto-fit on this axis. call before Begin()
SDXLLibrary_API void SDXL_ImGui_SetNextWindowSizeConstraints(const SDXL::float2& size_min, const SDXL::float2& size_max); // set next window size limits. use -1,-1 on either X/Y axis to preserve the current size. Sizes will be rounded down. Use callback to apply non-trivial programmatic constraints.
SDXLLibrary_API void SDXL_ImGui_SetNextWindowContentSize(const SDXL::float2& size);                               // set next window content size (~ scrollable client area, which enforce the range of scrollbars). Not including window decorations (title bar, menu bar, etc.) nor WindowPadding. set an axis to SDXL_ImGuiCond::Always.0f to leave it automatic. call before Begin()
SDXLLibrary_API void SDXL_ImGui_SetNextWindowCollapsed(bool collapsed, SDXL_ImGuiCond cond = SDXL_ImGuiCond::Always);                 // set next window collapsed state. call before Begin()
SDXLLibrary_API void SDXL_ImGui_SetNextWindowFocus();                                                       // set next window to be focused / top-most. call before Begin()
SDXLLibrary_API void SDXL_ImGui_SetNextWindowBgAlpha(float alpha);                                          // set next window background color alpha. helper to easily override the Alpha component of ImGuiCol_WindowBg/ChildBg/PopupBg. you may also use ImGuiWindowFlags_NoBackground.
SDXLLibrary_API void SDXL_ImGui_SetWindowPos(const SDXL::float2& pos, SDXL_ImGuiCond cond = SDXL_ImGuiCond::Always);                        // (not recommended) set current window position - call within Begin()/End(). prefer using SetNextWindowPos(), as this may incur tearing and side-effects.
SDXLLibrary_API void SDXL_ImGui_SetWindowSize(const SDXL::float2& size, SDXL_ImGuiCond cond = SDXL_ImGuiCond::Always);                      // (not recommended) set current window size - call within Begin()/End(). set to SDXL::float2(0,0) to force an auto-fit. prefer using SetNextWindowSize(), as this may incur tearing and minor side-effects.
SDXLLibrary_API void SDXL_ImGui_SetWindowCollapsed(bool collapsed, SDXL_ImGuiCond cond = SDXL_ImGuiCond::Always);                     // (not recommended) set current window collapsed state. prefer using SetNextWindowCollapsed().
SDXLLibrary_API void SDXL_ImGui_SetWindowFocus();                                                           // (not recommended) set current window to be focused / top-most. prefer using SetNextWindowFocus().
SDXLLibrary_API void SDXL_ImGui_SetWindowFontScale(float scale);                                            // set font scale. Adjust IO.FontGlobalScale if you want to scale all windows. This is an old API! For correct scaling, prefer to reload font + rebuild ImFontAtlas + call style.ScaleAllSizes().
SDXLLibrary_API void SDXL_ImGui_SetWindowPos(const char* name, const SDXL::float2& pos, SDXL_ImGuiCond cond = SDXL_ImGuiCond::Always);      // set named window position.
SDXLLibrary_API void SDXL_ImGui_SetWindowSize(const char* name, const SDXL::float2& size, SDXL_ImGuiCond cond = SDXL_ImGuiCond::Always);    // set named window size. set axis to SDXL_ImGuiCond::Always.0f to force an auto-fit on this axis.
SDXLLibrary_API void SDXL_ImGui_SetWindowCollapsed(const char* name, bool collapsed, SDXL_ImGuiCond cond = SDXL_ImGuiCond::Always);   // set named window collapsed state
SDXLLibrary_API void SDXL_ImGui_SetWindowFocus(const char* name);                                           // set named window to be focused / top-most. use NULL to remove focus.


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
// * ----- Main ---- *
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
// * ----- Drag ---- *
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
// * ---- Slider --- *
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
// * ---- Input ---- *
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

// **---------------**
// * - Selectable -- *
// **---------------**
SDXLLibrary_API bool SDXL_ImGui_Selectable(const char* label, bool selected = false, SDXL_ImGuiSelectableFlags flags = SDXL_ImGuiSelectableFlags::None, const SDXL::float2 & size = SDXL::float2(0, 0));  // "bool selected" carry the selection state (read-only). Selectable() is clicked is returns true so you can modify your selection state. size.x==0.0: use remaining width, size.x>0.0: specify width. size.y==0.0: use label height, size.y>0.0: specify height
SDXLLibrary_API bool SDXL_ImGui_Selectable(const char* label, bool* p_selected, SDXL_ImGuiSelectableFlags flags = SDXL_ImGuiSelectableFlags::None, const SDXL::float2& size = SDXL::float2(0, 0));       // "bool* p_selected" point to the selection state (read-write), as a convenient helper.


// **---------------**
// * --- ListBox --- *
// **---------------**
SDXLLibrary_API bool SDXL_ImGui_ListBox(const char* label, int* current_item, const char* const items[], int items_count, int height_in_items = -1);
SDXLLibrary_API bool SDXL_ImGui_ListBox(const char* label, int* current_item, bool (*items_getter)(void* data, int idx, const char** out_text), void* data, int items_count, int height_in_items = -1);
// EXAMPLE const char* listbox_items[] = { "Apple", "Banana", "Cherry", "Kiwi", "Mango", "Orange", "Pineapple", "Strawberry", "Watermelon" }; static int listbox_item_current = 1; SDXL_ImGui_ListBox("listbox\n(single select)", &listbox_item_current, listbox_items, 9, 4);
SDXLLibrary_API bool SDXL_ImGui_BeginListBox(const char* label, const SDXL::float2& size = SDXL::float2(0, 0)); // use if you want to reimplement ListBox() will custom data or interactions. if the function return true, you can output elements then call ListBoxFooter() afterwards.
SDXLLibrary_API bool SDXL_ImGui_BeginListBox(const char* label, int items_count, int height_in_items = -1); // "
SDXLLibrary_API void SDXL_ImGui_EndListBox();

// **---------------**
// * --- ListBox --- *
// **---------------**
  // - Use BeginMenuBar() on a window ImGuiWindowFlags_MenuBar to append to its menu bar.
	// - Use BeginMainMenuBar() to create a menu bar at the top of the screen and append to it.
	// - Use BeginMenu() to create a menu. You can call BeginMenu() multiple time with the same identifier to append more items to it.
SDXLLibrary_API bool SDXL_ImGui_BeginMenuBar();                                                     // append to menu-bar of current window (requires ImGuiWindowFlags_MenuBar flag set on parent window).
SDXLLibrary_API void SDXL_ImGui_EndMenuBar();                                                       // only call EndMenuBar() if BeginMenuBar() returns true!
SDXLLibrary_API bool SDXL_ImGui_BeginMainMenuBar();                                                 // create and append to a full screen menu-bar.
SDXLLibrary_API void SDXL_ImGui_EndMainMenuBar();                                                   // only call EndMainMenuBar() if BeginMainMenuBar() returns true!
SDXLLibrary_API bool SDXL_ImGui_BeginMenu(const char* label, bool enabled = true);                  // create a sub-menu entry. only call EndMenu() if this returns true!
SDXLLibrary_API void SDXL_ImGui_EndMenu();                                                          // only call EndMenu() if BeginMenu() returns true!
SDXLLibrary_API bool SDXL_ImGui_MenuItem(const char* label, const char* shortcut = NULL, bool selected = false, bool enabled = true);  // return true when activated. shortcuts are displayed for convenience but not processed by ImGui at the moment
SDXLLibrary_API bool SDXL_ImGui_MenuItem(const char* label, const char* shortcut, bool* p_selected, bool enabled = true);              // return true when activated + toggle (*p_selected) if p_selected != NULL







#endif