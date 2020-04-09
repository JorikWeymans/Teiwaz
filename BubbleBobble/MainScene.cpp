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
		LoadBackground();
		auto obj = new tyr::SceneObject(tyr::Transform(tyr::Vector2(378.f, 560), tyr::Vector2(1,1)));
		AddSceneObject(obj);

		const auto pivotMode = tyr::PivotMode::Center;
		m_pTexture = new tyr::TextureComp(L"BBSprites/Sprites_Sliced_Combined_Scaled.png", pivotMode, tyr::Rect(0.f, 0.f, 48.f, 48.f));

		obj->AddComponent(m_pTexture);
		obj->AddComponent(new tyr::ColliderComp(48,48, pivotMode, true	));

		m_pController = new tyr::CharacterControllerComp();
		obj->AddComponent(m_pController);
		
		
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
#ifdef USE_IM_GUI
		auto pFPS = new tyr::SceneObject(tyr::Transform(tyr::Vector2(650, 670)));
		AddSceneObject(pFPS);
		pFPS->AddComponent(new tyr::TextComp(L"Fonts/Arcade_20.fnt", L"Text", ColorYellow));
		pFPS->AddComponent(new tyr::TextComp(L"Fonts/Arcade_20.fnt", L"Text 1234.00", ColorRed, tyr::Vector2(0, 20)));
		pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::Update, 0));
		pFPS->AddComponent(new tyr::FPSComp(tyr::FPSCompType::FixedUpdate, 1));
#endif	
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
		m_pController->Move(-150 * elapsed, 0);
	
	
	}
	if (m_pContext->pInput->IsActionTriggered("MoveRight"))
		
	{
		m_Ani->SetAnimation("Walking");
		const float elapsed = m_pContext->pTime->fixedDeltaTime;
	
		m_pController->Move(150 * elapsed, 0);
	}

	if (m_pContext->pInput->IsActionTriggered("MoveDown"))
	{
		const float elapsed = m_pContext->pTime->fixedDeltaTime;

		m_Ani->SetAnimation("Eating");
		m_pController->Move(0, -150 * elapsed);


	}
	if (m_pContext->pInput->IsActionTriggered("MoveUp"))

	{
		m_Ani->SetAnimation("Walking");
		const float elapsed = m_pContext->pTime->fixedDeltaTime;

		m_pController->Move(0,150 * elapsed);
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
	const float scale = 3.f * 8.f; //game scale from original scale;

	vec.clear();
	reader.moveBufferPosition(sizeof(int) * 25 * /*13*/ 2);
	std::vector<tyr::SceneObject*> pObjects{};


	const int rows = 25;
	const int columns = 32;
	//                                filled hascoll
	std::vector<std::vector<std::pair<bool, bool>>> filled{};
	filled.resize(rows);
	for(auto& b : filled)
	{
		b.resize(columns);
	}

	//bool filled[25][32];
	for (int i{ 0 }; i < rows; i++)
	{
		//           BIG to LITTLE
		auto read = _byteswap_ulong(reader.Read<unsigned int>());
		
		for (int j{ sizeof(read) * 8U - 1 }; j >= 0; --j)
		{
			filled[i][columns - 1 - j].second = false;
			if (read & (1u << j))
			{
				filled[i][columns - 1 - j].first = true;
				
			}
			else
				filled[i][columns -1 -j].first = false;
		}
	}
	for(const auto v: filled)
	{
		for(const auto b : v)
		{
			OutputDebugStringA(std::to_string(b.first ? 1 : 0).c_str());
		}
		OutputDebugStringA("\n");
	}

	//bool foundTile = false;
	//tyr::Vector2 tilePos{ 0.f,0.f };
	for(int i {0}; i < rows ; i++)
	{
		for(int j{0}; j < columns; j++)
		{
			OutputDebugStringA(std::to_string(filled[i][j].first ? 1 : 0).c_str());
			if(filled[i][j].first == true)
			{
				tyr::Vector2 thePos{ j * scale,m_pContext->pGameSpace->height - (2 * scale) - i * scale };
				auto pinkSquare = new tyr::SceneObject(tyr::Transform(thePos, tyr::Vector2(1.f, 1.f)));
				AddSceneObject(pinkSquare);
				
				//pinkSquare->AddComponent(new tyr::ColliderComp(24, 24, tyr::PivotMode::TopLeft, false));
				
				
				int index = j;
				int amountFound = 1;
				//int rowIndex = i;
				int rowAmountfound = 1;
				//GO over each cell in a row, until you found one that is empty
				while (true)
				{
					index++;
					
					if (index > (columns - 1))
						break;
					
					
						if (filled[i][index].first == true && !filled[i][index].second)
						{
							//if (filled[i][j].second)
							//{
							//	break;
							//}
							amountFound++;
							//while (!(rowIndex > rows - 1))
							//{
							//	if (filled[rowIndex][index - 1].first == true && filled[rowIndex][index].first == true)
							//	{
							//		filled[rowIndex][index - 1].second = true;
							//		filled[rowIndex][index].second = true;
							//		rowIndex++;
							//		rowAmountfound++;
							//	}
							//	else
							//		break;
							//}
					
						}
					
					else
						break;
				
				
				}
				for(int k{0}; k < amountFound; ++k)
					{
					//pinkSquare->AddComponent(new tyr::TextureComp(L"BBSprites/blocksScaled.png", tyr::PivotMode::TopLeft,
					//	tyr::Rect(48, 0, 24, 24), tyr::Vector2(scale * k - scale, 0.f)));
					}					
				pinkSquare->AddComponent(new tyr::ColliderComp(scale * amountFound, scale * rowAmountfound, tyr::PivotMode::TopLeft, false));
				
				j = index;
				
			
			}
		}
		OutputDebugStringA("\n");
	}


}
