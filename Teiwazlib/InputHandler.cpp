#include "tyrpch.h"
#include "InputHandler.h"
#include <Xinput.h>
#include <algorithm>
#include <sstream>
tyr::InputHandler::InputHandler()
	//: m_pControllerState(new XINPUT_STATE())
	//, m_pControllerStatePrevious(nullptr)
	: m_Buttons(std::map<std::string, MappedButton*>())
{
	ZeroMemory(&m_pControllerState, sizeof(XINPUT_STATE));
}

tyr::InputHandler::~InputHandler()
{
	std::for_each(m_Buttons.begin(), m_Buttons.end(), [](auto& mappedButton) {delete mappedButton.second; mappedButton.second = nullptr; });
	m_Buttons.clear();
}

void tyr::InputHandler::Update()
{
	m_pControllerStatePrevious = m_pControllerState;

	ZeroMemory(&m_pControllerState, sizeof(XINPUT_STATE));
	XInputGetState(0, &m_pControllerState);

	for (auto mappedButton : m_Buttons)
	{
		auto b = mappedButton.second;
	
		switch (b->state)
		{
		case ButtonState::Pressed:
			if (m_pControllerState.Gamepad.wButtons == static_cast<WORD>(b->button) &&
				m_pControllerStatePrevious.Gamepad.wButtons != static_cast<WORD>(b->button))
			{
				b->IsTriggered = true;
			}
			else
			{
				b->IsTriggered = false;
			}
			break;
		case ButtonState::Down:
			if (m_pControllerState.Gamepad.wButtons == static_cast<WORD>(b->button))
			{
				b->IsTriggered = true;
			}
			else
			{
				b->IsTriggered = false;
			}
			break;
		case ButtonState::Released:
			if (m_pControllerState.Gamepad.wButtons != static_cast<WORD>(b->button) &&
				m_pControllerStatePrevious.Gamepad.wButtons == static_cast<WORD>(b->button))
			{
				b->IsTriggered = true;
			}
			else
			{
				b->IsTriggered = false;
			}
			break;
		}
	}
	
}

void tyr::InputHandler::AddButton(const std::string& name, ControllerButton button, ButtonState state)
{
	const auto found = m_Buttons.find(name);
	if(found == m_Buttons.end())
	{
		m_Buttons.insert({ name, new MappedButton(button, state) });
	}
}

bool tyr::InputHandler::IsButtonTriggered(const std::string& name)
{
	const auto found = m_Buttons.find(name);
	if (found == m_Buttons.end()) return false;

	return found->second->IsTriggered;
}
