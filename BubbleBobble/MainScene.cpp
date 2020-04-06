#include "stdafx.h"
#include "MainScene.h"
#include "Transform.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryReader.h"
#include "TyrFunctions.h"
#include "GameContext.h"
#include "InputHandler.h"
#include "Time.h"
void bub::MainScene::Initialize()
{
	LoadBackground();
	m_pPlayer = new tyr::SceneObject(tyr::transform(tyr::Vector2(28.f, 0.0f), tyr::Vector2(-1,1)));
	AddSceneObject(m_pPlayer);
	m_pPlayer->AddComponent(new tyr::TextureComp(L"BBSprites/spritesSCALED.png", tyr::PivotMode::TopCenter, tyr::Rectangle(48.f,48.f,48.f,48.f)));



	auto pFPS = new tyr::SceneObject(tyr::transform(tyr::Vector2(650, 10.0f)));
	AddSceneObject(pFPS);
	pFPS->AddComponent(new tyr::TextComp(L"Fonts/Arcade_20.fnt", L"Text", ColorYellow));
	pFPS->AddComponent(new tyr::TextComp(L"Fonts/Arcade_20.fnt", L"Text 1234.00", ColorRed, tyr::Vector2(0, 20)));
	pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::Update, 0));
	pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::FixedUpdate, 1));



	
	m_pContext->pInput->AddAction("MoveLeft", tyr::ButtonState::Down, VK_LEFT);
	m_pContext->pInput->AddAction("MoveRight", tyr::ButtonState::Down, VK_RIGHT);
	
}

void bub::MainScene::Update()
{
	tyr::Scene::Update();


	
}

void bub::MainScene::FixedUpdate()
{
	tyr::Scene::FixedUpdate();
	if (m_pContext->pInput->IsActionTriggered("MoveLeft"))
	{
		const float elapsed = m_pContext->pTime->fixedDeltaTime;

		m_pPlayer->Translate(-150 * elapsed, 0);

	}
	if (m_pContext->pInput->IsActionTriggered("MoveRight"))
	{
		const float elapsed = m_pContext->pTime->fixedDeltaTime;

		m_pPlayer->Translate(150 * elapsed, 0);
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
