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
#include "TyrException.h"
#include "Animation.h"
#include "Animator.h"


bub::MainScene::~MainScene()
{
	delete m_Ani;
	m_Ani = nullptr;
}

void bub::MainScene::Initialize()
{
	try
	{
		LoadBackground();
		//m_pPlayer = new tyr::SceneObject(tyr::Transform(tyr::Vector2(28.f, 0.0f), tyr::Vector2(1,1)));
		//AddSceneObject(m_pPlayer);

		//m_pTexture = new tyr::TextureComp(L"BBSprites/Sprites_Sliced_Combined_Scaled.png", tyr::PivotMode::TopCenter, tyr::Rect(0.f, 0.f, 48.f, 48.f));

		//m_pPlayer->AddComponent(m_pTexture);

		
		
		//m_pContext->pInput->AddAction("MoveLeft", tyr::ButtonState::Down, VK_LEFT);
		//m_pContext->pInput->AddAction("MoveRight", tyr::ButtonState::Down, VK_RIGHT);
		//m_pContext->pInput->AddAction("Abutton", tyr::ButtonState::Down, 'A');
		//
		////for (unsigned int i{ 0 }; i < 8; i++)
		////{
		////	m_AniSprites.emplace_back(Rect(i * 48.f, 0.f, 48, 48));
		////}
		//
		//
		////TODO: Add component, animatorComp with datamember Animator given to paramater;
		//
		//m_Ani = new tyr::Animator();
		//
		//auto walkAni = new tyr::Animation(.25f, tyr::SpritePositions{   {0, tyr::Rect(0.f ,0.f,48,48)},
		//																	{1, tyr::Rect(48.f,0.f,48,48)},
		//																	{2, tyr::Rect(48.f * 2,0.f,48,48)} ,
		//																	{3, tyr::Rect(48.f * 3,0.f,48,48)} });
		//
		//
		//auto EatAni = new tyr::Animation(.25f, tyr::SpritePositions{ {0, tyr::Rect(0.f + 4 * 48.f ,0.f,48,48)},
		//																{1, tyr::Rect(48.f + 4 * 48.f,0.f,48,48)},
		//																{2, tyr::Rect(48.f * 2 + 4 * 48.f,0.f,48,48)} ,
		//																{3, tyr::Rect(48.f * 3 + 4 * 48.f,0.f,48,48)} });
		//
		//
		//m_Ani->AddAnimation("Walking", walkAni);
		//m_Ani->AddAnimation("Eating", EatAni);
		//m_Ani->SetAnimation("Walking");

		
	}
	catch(tyr::TyrException& e)
	{
		MessageBoxW(NULL, e.what(), L"Error", MB_ICONERROR);
	}
	
}

void bub::MainScene::Update()
{
	tyr::Scene::Update();
	//m_Ani->Update(m_pContext->pTime->deltaTime);
	//m_pTexture->SetSourceRect(m_Ani->GetCurrentAnimation());

	
}

void bub::MainScene::FixedUpdate()
{
	tyr::Scene::FixedUpdate();
	//if (m_pContext->pInput->IsActionTriggered("MoveLeft"))
	//{
	//	const float elapsed = m_pContext->pTime->fixedDeltaTime;
	//	
	//	m_Ani->SetAnimation("Eating");
	//	m_pPlayer->Translate(-150 * elapsed, 0);
	//
	//
	//}
	//if (m_pContext->pInput->IsActionTriggered("MoveRight"))
	//	
	//{
	//	m_Ani->SetAnimation("Walking");
	//	const float elapsed = m_pContext->pTime->fixedDeltaTime;
	//
	//	m_pPlayer->Translate(150 * elapsed, 0);
	//}

}

void bub::MainScene::Render() const
{
	tyr::Scene::Render();


}
#ifdef USE_IM_GUI
void bub::MainScene::Debug()
{

	SDXL_ImGui_Begin("test");
	SDXL_ImGui_DragFloat2("floaty", &m_pPlayer->Transform()->position.x, 1, 0.f, 1260);

	SDXL_ImGui_End();
}
#endif

void bub::MainScene::LoadBackground()
{
	tyr::BinaryReader reader{ L"./Data/BBSprites/leveldata.dat" };
	//tyr::BinaryReader reader{ L"./Data/BBSprites/Level/FixedLevelData.dat" };

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
		auto k = sizeof(read);
		
		pos.x = (sizeof(read) * 8U - 1) * scale;
		for (int j{ sizeof(read) * 8U - 1 }; j >= 0; --j)
		{
			pos.x = ((sizeof(read) * 8U - 1) * scale) - j * scale;

			if (read & (1u << j))
			{
				//1
				auto pinkSquare = new tyr::SceneObject(tyr::Transform(pos, tyr::Vector2(scale, scale)));
				AddSceneObject(pinkSquare);
				pinkSquare->AddComponent(new tyr::TextureComp(L"Textures/1x1Pink.png"));
			}
		}
	}


	auto pFPS = new tyr::SceneObject(tyr::Transform(tyr::Vector2(650, 10.0f)));
	AddSceneObject(pFPS);
	pFPS->AddComponent(new tyr::TextComp(L"Fonts/Arcade_20.fnt", L"Text", ColorYellow));
	pFPS->AddComponent(new tyr::TextComp(L"Fonts/Arcade_20.fnt", L"Text 1234.00", ColorRed, tyr::Vector2(0, 20)));
	pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::Update, 0));
	pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::FixedUpdate, 1));
}
