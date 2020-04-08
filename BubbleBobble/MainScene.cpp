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
#include "Vectors.h"

bub::MainScene::~MainScene()
{
	delete m_Ani;
	m_Ani = nullptr;
}

void bub::MainScene::Initialize()
{
	try
	{
		//LoadBackground();
		m_pPlayer = new tyr::SceneObject(tyr::Transform(tyr::Vector2(28.f, 624.f), tyr::Vector2(1,1)));
		AddSceneObject(m_pPlayer);

		auto pivotMode = tyr::PivotMode::Center;
		m_pTexture = new tyr::TextureComp(L"BBSprites/Sprites_Sliced_Combined_Scaled.png", pivotMode, tyr::Rect(0.f, 0.f, 48.f, 48.f));

		m_pPlayer->AddComponent(m_pTexture);
		m_pPlayer->AddComponent(new tyr::ColliderComp(48,48, pivotMode));

		
		
		m_pContext->pInput->AddAction("MoveUp", tyr::ButtonState::Down, 'W' );
		m_pContext->pInput->AddAction("MoveDown", tyr::ButtonState::Down, 'S');
		
		m_pContext->pInput->AddAction("MoveLeft", tyr::ButtonState::Down, 'A');
		m_pContext->pInput->AddAction("MoveRight", tyr::ButtonState::Down, 'D');
		//
		////for (unsigned int i{ 0 }; i < 8; i++)
		////{
		////	m_AniSprites.emplace_back(Rect(i * 48.f, 0.f, 48, 48));
		////}
		//
		//
		////TODO: Add component, animatorComp with datamember Animator given to paramater;
		//
		m_Ani = new tyr::Animator();
		
		auto walkAni = new tyr::Animation(.25f, tyr::SpritePositions{   {0, tyr::Rect(0.f ,0.f,48,48)},
																			{1, tyr::Rect(48.f,0.f,48,48)},
																			{2, tyr::Rect(48.f * 2,0.f,48,48)} ,
																			{3, tyr::Rect(48.f * 3,0.f,48,48)} });
		
		
		auto EatAni = new tyr::Animation(.25f, tyr::SpritePositions{ {0, tyr::Rect(0.f + 4 * 48.f ,0.f,48,48)},
																		{1, tyr::Rect(48.f + 4 * 48.f,0.f,48,48)},
																		{2, tyr::Rect(48.f * 2 + 4 * 48.f,0.f,48,48)} ,
																		{3, tyr::Rect(48.f * 3 + 4 * 48.f,0.f,48,48)} });
		
		
		m_Ani->AddAnimation("Walking", walkAni);
		m_Ani->AddAnimation("Eating", EatAni);
		m_Ani->SetAnimation("Walking");


		//auto pinkSquare = new tyr::SceneObject(tyr::Transform(tyr::Vector2{0,0}, tyr::Vector2(1, 1)));
		//AddSceneObject(pinkSquare);
		//pinkSquare->AddComponent(new tyr::TextureComp(L"BBSprites/Sprites_Sliced_Combined_Scaled.png", tyr::PivotMode::TopLeft, tyr::Rect(0, 0, 16, 16)));

		auto pFPS = new tyr::SceneObject(tyr::Transform(tyr::Vector2(650, 650)));
		AddSceneObject(pFPS);
		pFPS->AddComponent(new tyr::TextComp(L"Fonts/Arcade_20.fnt", L"Text", ColorYellow));
		pFPS->AddComponent(new tyr::TextComp(L"Fonts/Arcade_20.fnt", L"Text 1234.00", ColorRed, tyr::Vector2(0, 20)));
		pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::Update, 0));
		pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::FixedUpdate, 1));
		
	}
	catch(tyr::TyrException& e)
	{
		MessageBoxW(NULL, e.what(), L"Error", MB_ICONERROR);
	}


	
}

void bub::MainScene::Update()
{
	tyr::Scene::Update();
	m_Ani->Update(m_pContext->pTime->deltaTime);
	m_pTexture->SetSourceRect(m_Ani->GetCurrentAnimation());
	
}

void bub::MainScene::FixedUpdate()
{
	tyr::Scene::FixedUpdate();
	if (m_pContext->pInput->IsActionTriggered("MoveLeft"))
	{
		const float elapsed = m_pContext->pTime->fixedDeltaTime;
		
		m_Ani->SetAnimation("Eating");
		m_pPlayer->Translate(-150 * elapsed, 0);
	
	
	}
	if (m_pContext->pInput->IsActionTriggered("MoveRight"))
		
	{
		m_Ani->SetAnimation("Walking");
		const float elapsed = m_pContext->pTime->fixedDeltaTime;
	
		m_pPlayer->Translate(150 * elapsed, 0);
	}

	if (m_pContext->pInput->IsActionTriggered("MoveDown"))
	{
		const float elapsed = m_pContext->pTime->fixedDeltaTime;

		m_Ani->SetAnimation("Eating");
		m_pPlayer->Translate(0, -150 * elapsed);


	}
	if (m_pContext->pInput->IsActionTriggered("MoveUp"))

	{
		m_Ani->SetAnimation("Walking");
		const float elapsed = m_pContext->pTime->fixedDeltaTime;

		m_pPlayer->Translate(0,150 * elapsed);
	}

}

void bub::MainScene::Render() const
{
	tyr::Scene::Render();


}
#ifdef USE_IM_GUI

void bub::MainScene::Debug()
{
	tyr::Scene::Debug();
	SDXL_ImGui_Begin("Debug");
	
	
	//SDXL_ImGui_SliderFloat2("position", &m_pPlayer->Transform()->position.x, 0.f, 100.f);
	
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

	tyr::Vector2 pos(0, m_pContext->pGameSpace->height);

	vec.clear();
	reader.moveBufferPosition(sizeof(int) * 25 * 1);

	for (int i{ 0 }; i < 25; i++)
	{
		//           BIG to LITTLE
		auto read = _byteswap_ulong(reader.Read<unsigned int>());
		//auto read = reader.Read<unsigned int>();
		pos.y = m_pContext->pGameSpace->height - ((scale * 2) + i * scale);
		pos.x = (sizeof(read) * 8U - 1) * scale;
		
		for (int j{ sizeof(read) * 8U - 1 }; j >= 0; --j)
		{
			pos.x = ((sizeof(read) * 8U - 1) * scale) - j * scale;

			if (read & (1u << j))
			{
				//1
				auto pinkSquare = new tyr::SceneObject(tyr::Transform(pos, tyr::Vector2(1.f, 1.f)));
				AddSceneObject(pinkSquare);
				//pinkSquare->AddComponent(new tyr::TextureComp(L"Textures/1x1Pink.png"));
				pinkSquare->AddComponent(new tyr::TextureComp(L"BBSprites/blocksScaled.png", tyr::PivotMode::TopLeft, tyr::Rect(48,0,24,24)));
			}
		}
	}



}
