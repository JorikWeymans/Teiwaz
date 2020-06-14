#pragma once
#include <map>
#include <Xinput.h>
#include <vector>

#define KEYBOARD_SIZE 256
namespace tyr
{
	enum class ControllerButton : WORD
	{
		None        = 0xFFFF,
		ButtonA     = XINPUT_GAMEPAD_A,
		ButtonB     = XINPUT_GAMEPAD_B,
		ButtonX     = XINPUT_GAMEPAD_X,
		ButtonY     = XINPUT_GAMEPAD_Y,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonLS    = XINPUT_GAMEPAD_LEFT_SHOULDER,
		ButtonRS    = XINPUT_GAMEPAD_RIGHT_SHOULDER,
		ButtonUp    = XINPUT_GAMEPAD_DPAD_UP,
		ButtonDown  = XINPUT_GAMEPAD_DPAD_DOWN,
		ButtonLeft  = XINPUT_GAMEPAD_DPAD_LEFT,
		ButtonRight = XINPUT_GAMEPAD_DPAD_RIGHT,
	};
	enum class ButtonState : WORD
	{
		Pressed,
		Down,
		Released
	};
	struct MappedAction
	{
		explicit MappedAction(ControllerButton b, ButtonState s, int key)
		: button(b), key(key), state(s), IsTriggered(false) {}
		ControllerButton button;
		int key;
		ButtonState state;
		bool IsTriggered;
	};


	
	class InputHandler final
	{
	public:
		InputHandler();
		~InputHandler();

		void Update();
		// Key -1 means no keyboard action, button == ControllerButton::None means no controller button, both can be used at the same time
		void AddAction(const std::string& name, ButtonState state, int key = -1, ControllerButton button = ControllerButton::None);
		bool IsActionTriggered(const std::string& name);

	private:
		XINPUT_STATE *m_ControllerState, *m_ControllerStatePrevious;
		BYTE *m_KeyboardState, *m_KeyboardStatePrevious;
		std::map<std::string, MappedAction*> m_Actions;
		
		
	public:
		InputHandler(const InputHandler&) = delete;
		InputHandler(InputHandler&&) = delete;
		InputHandler& operator=(const InputHandler&) = delete;
		InputHandler& operator=(InputHandler&&) = delete;
	};


}
