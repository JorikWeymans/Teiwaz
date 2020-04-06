#include "tyrpch.h"
#include "InputHandler.h"
#include <Xinput.h>
#include <algorithm>
#include <sstream>
#include "TyrFunctions.h"
tyr::InputHandler::InputHandler()
	: m_ControllerState(new XINPUT_STATE())
	, m_ControllerStatePrevious(static_cast<XINPUT_STATE*>(malloc(sizeof(XINPUT_STATE))))
	, m_KeyboardState(new BYTE[KEYBOARD_SIZE])
	, m_KeyboardStatePrevious(static_cast<BYTE*>(malloc(KEYBOARD_SIZE))) //sizeof(BYTE) * KEYBOARD_SIZE == redundant cuz sizeof(BYTE) == 1
	, m_Actions(std::map<std::string, MappedAction*>())
{
	ZeroMemory(m_ControllerState, sizeof(XINPUT_STATE));
	if(m_ControllerStatePrevious) ZeroMemory(m_ControllerStatePrevious, sizeof(XINPUT_STATE));

	ZeroMemory(m_KeyboardState, KEYBOARD_SIZE);
	if(m_KeyboardStatePrevious) ZeroMemory(m_KeyboardStatePrevious, KEYBOARD_SIZE);

}

tyr::InputHandler::~InputHandler()
{
	//Controller
	delete m_ControllerState;
	m_ControllerState = nullptr;
	
	free(m_ControllerStatePrevious);

	//Keyboard
	delete[] m_KeyboardState;
	m_KeyboardState = nullptr;

	free(m_KeyboardStatePrevious);

	
	std::for_each(m_Actions.begin(), m_Actions.end(), [](auto& mappedButton) {delete mappedButton.second; mappedButton.second = nullptr; });
	m_Actions.clear();
}

void tyr::InputHandler::Update()
{

	//Controller state
	memcpy(m_ControllerStatePrevious, m_ControllerState, sizeof(XINPUT_STATE));
	
	ZeroMemory(m_ControllerState, sizeof(XINPUT_STATE));
	XInputGetState(0, m_ControllerState);

	//Keyboard state
	memcpy(m_KeyboardStatePrevious, m_KeyboardState, KEYBOARD_SIZE);
	
	ZeroMemory(m_KeyboardState, KEYBOARD_SIZE);
	const bool success = GetKeyboardState(m_KeyboardState);
	if (!success)
		return;

	
	for (auto& mappedButton : m_Actions)
	{
		auto b = mappedButton.second;
		b->IsTriggered = false;
		
		switch (b->state)
		{
		case ButtonState::Pressed:
			//controller
			if(b->button != ControllerButton::None)
			{
				if (m_ControllerState->Gamepad.wButtons == static_cast<WORD>(b->button) &&
					m_ControllerStatePrevious->Gamepad.wButtons != static_cast<WORD>(b->button))
				{
					b->IsTriggered = true;
				}
			}
			//Keyboard
			if (b->key != -1)
			{
				if (m_KeyboardState[static_cast<unsigned int>(b->key)] & 0x80 &&
					!(m_KeyboardStatePrevious[static_cast<unsigned int>(b->key)] & 0x80))
				{
					b->IsTriggered = true;
				}
			}
			break;
		case ButtonState::Down:
			//controller
			if (b->button != ControllerButton::None)
			{
				if (m_ControllerState->Gamepad.wButtons == static_cast<WORD>(b->button))
				{
					b->IsTriggered = true;
				}
			}
			//Keyboard
			if (b->key != -1)
			{
				if (m_KeyboardState[static_cast<unsigned int>(b->key)] & 0x80)
				{
					b->IsTriggered = true;
				}
			}
			break;
		case ButtonState::Released:
			//controller
			if (b->button != ControllerButton::None)
			{
				if (m_ControllerState->Gamepad.wButtons != static_cast<WORD>(b->button) &&
					m_ControllerStatePrevious->Gamepad.wButtons == static_cast<WORD>(b->button))
				{
					b->IsTriggered = true;
				}
			}
			//Keyboard
			if(b->key != -1)
			{
				if(!(m_KeyboardState[static_cast<unsigned int>(b->key)] & 0x80) &&
					m_KeyboardStatePrevious[static_cast<unsigned int>(b->key)] & 0x80)
				{
					b->IsTriggered = true;
				}
			}
			break;
		}
	}
	
}

void tyr::InputHandler::AddAction(const std::string& name, ButtonState state, int key,ControllerButton button)
{
	const auto found = m_Actions.find(name);
	if(found == m_Actions.end())
	{
		m_Actions.insert({ name, new MappedAction(button, state, key) });
	}
}

bool tyr::InputHandler::IsButtonTriggered(const std::string& name)
{
	const auto found = m_Actions.find(name);
	if (found == m_Actions.end()) return false;

	return found->second->IsTriggered;
}
