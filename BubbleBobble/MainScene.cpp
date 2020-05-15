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
#include "BubPrefab.h"

bub::MainScene::MainScene()
	:tyr::Scene("MainScene")
{
}

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

		BubPrefab::Generate(this);
		

		//
		////for (unsigned int i{ 0 }; i < 8; i++)
		////{
		////	m_AniSprites.emplace_back(Rect(i * 48.f, 0.f, 48, 48));
		////}
		//
		//
		////TODO: Add component, animatorComp with datamember Animator given to paramater;
		//
		/*m_Ani = new tyr::Animator();
		
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
		m_Ani->SetAnimation("Walking");*/


		//auto pinkSquare = new tyr::SceneObject(tyr::Transform(tyr::Vector2{0,0}, tyr::Vector2(1, 1)));
		//AddSceneObject(pinkSquare);
		//pinkSquare->AddComponent(new tyr::TextureComp(L"BBSprites/Sprites_Sliced_Combined_Scaled.png", tyr::PivotMode::TopLeft, tyr::Rect(0, 0, 16, 16)));
	
#ifdef EDITOR_MODE
		auto pFPS = new tyr::SceneObject(tyr::Transform(tyr::Vector2(650, 670)), "FPS");
		AddSceneObject(pFPS);
		pFPS->AddComponent(new tyr::TextComp("Fonts/Arcade_20.fnt", "Text", ColorYellow));
		pFPS->AddComponent(new tyr::TextComp("Fonts/Arcade_20.fnt", "Text 1234.00", ColorRed, tyr::Vector2(0, 20)));
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
	//m_Ani->Update(m_pContext->pTime->deltaTime);
	//m_pTexture->SetSourceRect(m_Ani->GetCurrentAnimation());

}

void bub::MainScene::FixedUpdate()
{

	tyr::Scene::FixedUpdate();


}

void bub::MainScene::Render() const
{
	tyr::Scene::Render();


}
#ifdef EDITOR_MODE

void bub::MainScene::Debug()
{
	tyr::Scene::Debug();




	
}
#endif

void bub::MainScene::LoadBackground()
{
	tyr::BinaryReader reader{ "./Data/BBSprites/leveldata.dat" };
	//tyr::BinaryReader reader{ L"./Data/BBSprites/Level/FixedLevelData.dat" };

	if (!reader.IsOpen()) return;

	std::vector<std::string> vec{};
	const float scale = 3.f * 8.f; //game scale from original scale;

	vec.clear();
	reader.moveBufferPosition(sizeof(int) * 25 * 2 /*13*/ /*2*/);
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
			{
				if( j  < 2)
				{
					filled[i][columns - 1 - j].first = true;
				}
				else
					filled[i][columns - 1 - j].first = false;
			}
				
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


	auto pBackground = new tyr::SceneObject(tyr::Transform(tyr::Vector2(0.f, 0.f), tyr::Vector2(1.f, 1.f)), "Background");
	AddSceneObject(pBackground);
	for(int i {0}; i < rows ; i++)
	{
		for(int j{0}; j < columns; j++)
		{
			
			if(filled[i][j].first == true && !filled[i][j].second)
			{
				//filled[i][j].second = true;
				tyr::Vector2 thePos{ j * scale,m_pContext->pGameSpace->height - (2 * scale) - i * scale };
				auto pBlock = new tyr::SceneObject(tyr::Transform(thePos, tyr::Vector2(1.f, 1.f)));
				pBackground->AddChild(pBlock);

				
				int index = j;
				int amountFound = 1;
				
				//GO over each cell in a row, until you found one that is empty
				while (true)
				{
					index++;
					
					if (index > (columns - 1)) break;
					
					
					if (filled[i][index].first == true && !filled[i][index].second) amountFound++;
					else break;
				}
				
				int secondIndex = j;
				int y = i;
				int rowAmount = 1;

				//Go over each cell in a column, until one is found that is empty
				while(true)
				{
					if (secondIndex >= index) break;

					rowAmount = 1;
					bool fullBreak = false;
					while(true)
					{
						if (y + 1 > (rows - 1)) break;

						if (filled[y + 1][secondIndex].first &&  !filled[y + 1][secondIndex].second) rowAmount++;
						else
						{
							if(amountFound == 1)
							{
								fullBreak = true;
								break;
							}
							rowAmount = 1;
							fullBreak = true;
							break;
						}
						y++;
					}
					if (fullBreak) break;
					y = i;
					secondIndex ++;
				}


				int m = 0;
				int n = 0;
				for (int k{ i }; k <  i + rowAmount ; k++)
				{
					for (int l{ j }; l < j  + amountFound ; l++)
					{
						filled[k][l].second = true;

						pBlock->AddComponent(new tyr::TextureComp(3U, tyr::PivotMode::TopLeft,
								tyr::Rect(24, 0, 24, 24), tyr::Vector2(m * scale,n * scale)));

						m++;
					}
					m = 0;
					n++;
				}
				
				pBlock->AddComponent(new tyr::ColliderComp(scale * amountFound, scale * rowAmount, tyr::PivotMode::TopLeft, false));
				
				j = index;
				
			
			}
		}
	}
	OutputDebugStringA("\n---------------------------------------------\n");
	for (int i{ 0 }; i < rows; i++)
	{
		for (int j{ 0 }; j < columns; j++)
		{

			OutputDebugStringA(std::to_string(filled[i][j].second ? 1 : 0).c_str());
		}
		OutputDebugStringA("\n");
	}
	

}
