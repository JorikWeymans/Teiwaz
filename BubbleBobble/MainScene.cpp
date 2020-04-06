#include "stdafx.h"
#include "MainScene.h"
#include "Transform.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryReader.h"
#include "TyrFunctions.h"
#include "GameContext.h"
#include "InputHandler.h"
void bub::MainScene::Initialize()
{
	LoadBackground();
	
	m_pContext->pInput->AddAction("TestReleased", tyr::ButtonState::Released, -1,  tyr::ControllerButton::ButtonA);
	m_pContext->pInput->AddAction("TestPressed", tyr::ButtonState::Pressed, -1, tyr::ControllerButton::ButtonB);
	m_pContext->pInput->AddAction("TestDown", tyr::ButtonState::Down, -1,  tyr::ControllerButton::ButtonX);
}

void bub::MainScene::Update()
{
	tyr::Scene::Update();
	if(m_pContext->pInput->IsButtonTriggered("TestReleased"))
	{
		OutputDebugStringA("TestReleased\n");
	}

	if (m_pContext->pInput->IsButtonTriggered("TestPressed"))
	{
		OutputDebugStringA("TestPressed\n");
	}

	if (m_pContext->pInput->IsButtonTriggered("TestDown"))
	{
		OutputDebugStringA("TestDown\n");
	}
	
}

void bub::MainScene::LoadBackground()
{
	tyr::BinaryReader reader{ L"./Data/BBSprites/leveldata.dat" };

	if (!reader.IsOpen()) return;

	std::vector<std::string> vec{};
	float scale = 3.f * 8.f; //game scale from original scale;

	tyr::Vector2 pos(0, 0);

	vec.clear();
	reader.moveBufferPosition(sizeof(int) * 25 * 2);

	for (int i{ 0 }; i < 25; i++)
	{
		//           BIG to LITTLE
		auto read = _byteswap_ulong(reader.Read<unsigned int>());
		//auto str = tyr::ToBinaryString(read);
		pos.y = (scale * 2) + i * scale;
		pos.x = (sizeof(read) * 8U - 1) * scale;
		for (int j{ sizeof(read) * 8U - 1 }; j >= 0; --j)
		{
			pos.x = ((sizeof(read) * 8U - 1) * scale) - j * scale;

			if (read & (1u << j))
			{
				//1
				auto pinkSquare = new tyr::SceneObject(tyr::transform(pos, tyr::Vector2(scale, scale)));
				AddSceneObject(pinkSquare);
				pinkSquare->AddComponent(new tyr::TextureComp(L"Textures/1x1Pink.png"));
			}
		}
	}
}
