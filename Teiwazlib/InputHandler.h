#pragma once
#include <map>
#include <Xinput.h>
namespace tyr
{
	enum class ControllerButton : WORD
	{
		ButtonA     = XINPUT_GAMEPAD_A,
		ButtonB     = XINPUT_GAMEPAD_B,
		ButtonX     = XINPUT_GAMEPAD_X,
		ButtonY     = XINPUT_GAMEPAD_Y,
		ButtonStart = XINPUT_GAMEPAD_START,
		ButtonLS    = XINPUT_GAMEPAD_LEFT_SHOULDER,
		ButtonRS    = XINPUT_GAMEPAD_RIGHT_SHOULDER,
	};
	enum class ButtonState : WORD
	{
		Pressed,
		Down,
		Released
	};
	struct MappedButton
	{
		explicit MappedButton(ControllerButton b, ButtonState s)
		: button(b), state(s), IsTriggered(false) {}
		ControllerButton button;
		ButtonState state;
		bool IsTriggered;
	};

	class InputHandler final
	{
	public:
		InputHandler();
		~InputHandler();

		void Update();
		void AddButton(const std::string& name, ControllerButton button, ButtonState state);
		bool IsButtonTriggered(const std::string& name);

	private:
		XINPUT_STATE m_pControllerState;
		XINPUT_STATE m_pControllerStatePrevious; //weak pointer
		std::map<std::string, MappedButton*> m_Buttons;
		
		
	public:
		InputHandler(const InputHandler&) = delete;
		InputHandler(InputHandler&&) = delete;
		InputHandler& operator=(const InputHandler&) = delete;
		InputHandler& operator=(InputHandler&&) = delete;
	};


}
