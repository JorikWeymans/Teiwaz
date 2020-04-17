#include "tyrpch.h"
#include "Animation.h"
#include "BinaryWriter.h"
#include "BinaryReader.h"
#include <algorithm>

tyr::Animation::Animation(const std::string& animationName, float tpf,SpritePositions&& sp)
	: m_AnimationName(animationName)
	, m_AniElapser(tpf)
	, m_CurrentAnimation(0)

{
	m_AniSprites = std::move(sp);
	
	
}

tyr::Animation::Animation(const std::string& path)
{
	UNREFERENCED_PARAMETER(path);
	BinaryReader reader(path);

	
	ULONG64 header = reader.Read<ULONG64>();
	if (header != 0x78b109c3)
	{
#ifdef USE_IM_GUI
		SDXL_ImGui_ConsoleLogError("This is no an animation");
#else
		THROW_ERROR(L"This is not an animation");
#endif
	}
	m_AnimationName = reader.ReadString();
	m_AniElapser.Reset(reader.Read<float>());

	const UINT elements = reader.Read<UINT>();
	
	for(UINT i{0}; i < elements; ++i)
	{
		m_AniSprites.insert({ i, Rect(reader.Read<Rect_POD>()) });
	}

	
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

void tyr::Animation::Save()
{
	BinaryWriter writer("./Data/Animations/" + m_AnimationName + ".tyrAnimation");

	//Binsctructure
	// Long double -> Header (JorikWeymansTyrScene hashed via Adler32 to this value)
	// std::string -> AnimationName
	// float -> tpf
	// UINT -> AnimationCount
	// for each Ainimation
	//  Rect
	//  (no need to save the position because a map is auto sorted
	//

	ULONG64 header = 0x78b109c3;
	writer.Write(header);
	writer.Write(m_AnimationName);
	writer.Write(m_AniElapser.GetMax());
	writer.Write(static_cast<UINT>(m_AniSprites.size()));
	std::for_each(m_AniSprites.begin(), m_AniSprites.end(), [&writer](const auto& ani) { writer.Write(ani.second.ToPOD()); });
	


	

	
}
