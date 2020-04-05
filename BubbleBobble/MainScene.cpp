#include "stdafx.h"
#include "MainScene.h"
#include "Transform.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryReader.h"
#include "TyrFunctions.h"

void bub::MainScene::Initialize()
{
	//auto pBackground = new tyr::SceneObject(tyr::transform(tyr::Vector2(0.0f, 0.0f)));
	//AddSceneObject(pBackground);
	//pBackground->AddComponent(new tyr::TextureComp(L"Textures/Ref2.png"));
	//
	//float scale = 3.f * 8.f; //game scale from original scale;
	//
	//auto pinkSquare = new tyr::SceneObject(tyr::transform(tyr::Vector2(0.0f, 0.0f), tyr::Vector2(scale, scale)));
	//AddSceneObject(pinkSquare);
	//pinkSquare->AddComponent(new tyr::TextureComp(L"Textures/1x1Pink.png"));

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
			
			if(read& (1u << j))
			{
				//1
				auto pinkSquare = new tyr::SceneObject(tyr::transform(pos, tyr::Vector2(scale, scale)));
				AddSceneObject(pinkSquare);
				pinkSquare->AddComponent(new tyr::TextureComp(L"Textures/1x1Pink.png"));
			}
			else
			{
				//0
			}
		}
		
		
		
		//reader.moveBufferPosition(sizeof(int) * 9);
	
	}
}
