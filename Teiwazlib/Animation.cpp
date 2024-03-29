#include "tyrpch.h"
#include "Animation.h"
#include <algorithm>

#include "BinaryWriter.h"
#include "BinaryReader.h"

#include "TyrException.h"
#include "ContentManager.h"


#define ANIMATION_SUFFIX ".tyrAnimation"

tyr::Animation::Animation(const std::string& animationName, TextureID spriteID, float tpf,SpritePositions&& sp)
	: m_AnimationName(animationName)
	, m_SpriteID(spriteID)
	, m_AniElapser(tpf)
	, m_CurrentAnimation(0)

{
	m_AniSprites = std::move(sp);
	
	
}
tyr::Animation::Animation(float tpf)
	: m_AnimationName("NaN")
	, m_SpriteID(0)
	, m_AniElapser(tpf)
	, m_CurrentAnimation(0)
{

}

tyr::Animation::Animation() //Private constructor
	: m_AnimationName("NaN")
	, m_SpriteID(0)
	, m_AniElapser(0.25f)
	, m_CurrentAnimation(0)
{
}


tyr::Animation* tyr::Animation::Create(const std::string& path)
{
	
	BinaryReader reader(path + ANIMATION_SUFFIX);


	const ULONG64 header = reader.Read<ULONG64>();
	if (header != 0x78b109c3)
	{
		THROW_ERROR(L"This is not an animation");
	}

	Animation* pTheAnimation = new Animation();
	pTheAnimation->m_AnimationName = reader.ReadString();
	pTheAnimation->m_SpriteID = reader.Read<TextureID>();
	pTheAnimation->m_AniElapser.Reset(reader.Read<float>());

	
	const UINT elements = reader.Read<UINT>();

	pTheAnimation->m_AniSprites.resize(elements);

	for (UINT i{ 0 }; i < elements; ++i)
	{
		pTheAnimation->m_AniSprites[i] = Rect(reader.Read<Rect_POD>());
	}

	return pTheAnimation;
}



void tyr::Animation::Update(float elapsed)
{
	if(m_AniElapser.Update(elapsed))
	{
		m_CurrentAnimation++;
		if (m_CurrentAnimation >= m_AniSprites.size())
		{
		
			m_CurrentAnimation = 0;
		}
		m_AniElapser.Reset();
	}

}
const tyr::Rect& tyr::Animation::GetCurrentAnimation() const
{	
	return m_AniSprites.at(m_CurrentAnimation);
}

void tyr::Animation::Reset()
{
	m_AniElapser.Reset();
	m_CurrentAnimation = 0;
}
#ifdef EDITOR_MODE
void tyr::Animation::Save()
{
	std::stringstream ss;
	ss << CONTENT_MANAGER->GetAbsoluteAnimationFolder();
	ss << m_AnimationName;
	ss << ANIMATION_SUFFIX;
	
	BinaryWriter writer(ss.str());

	//Binsctructure
	// Long double -> Header (JorikWeymansTyrAnimation hashed via Adler32 to this value)
	// std::string -> AnimationName
	// float -> tpf
	// UINT -> AnimationCount
	// for each Ainimation
	//  Rect
	//  (no need to save the position because a map is auto sorted
	//

	if (writer.IsOpen())
	{
		const ULONG64 header = 0x78b109c3;
		writer.Write(header);
		writer.Write(m_AnimationName);
		writer.Write(m_SpriteID);
		writer.Write(m_AniElapser.GetMax());
		writer.Write(static_cast<UINT>(m_AniSprites.size()));
		std::for_each(m_AniSprites.begin(), m_AniSprites.end(), [&writer](const auto& ani) { writer.Write(ani.ToPOD()); });
	}
	else
		SDXL_ImGui_ConsoleLogWarning("Could not safe the animation");

}
tyr::Animation* tyr::Animation::GenerateNew(const std::string& name)
{
	Animation* pReturnAnimation = new Animation();
	pReturnAnimation->m_AnimationName = name;
	pReturnAnimation->Save();
	
	return pReturnAnimation;
}


#endif

tyr::Animation* tyr::Animation::CreateCopy()
{
	auto pReturn = new Animation();
	pReturn->m_AnimationName = this->m_AnimationName;
	pReturn->m_SpriteID = this->m_SpriteID;
	pReturn->m_AniElapser = this->m_AniElapser;
	pReturn->m_AniElapser.Reset();

	const int size = static_cast<int>(this->m_AniSprites.size());
	pReturn->m_AniSprites.resize(size);
	for (int i{ 0 }; i < size; i++)
	{
		pReturn->m_AniSprites[i] = this->m_AniSprites[i];
	}


	return pReturn;

}
bool tyr::operator==(Animation* lhs, const std::string& rhs)
{
	if (!lhs) return false;
	
	return lhs->m_AnimationName == rhs;
}
