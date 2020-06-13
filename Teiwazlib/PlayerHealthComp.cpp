#include "tyrpch.h"
#include "PlayerHealthComp.h"
#include "BinaryWriter.h"
tyr::PlayerHealthComp::PlayerHealthComp()
	: tyr::BaseComponent(ComponentType::PlayerHealth, "PlayerHealth Component")
	, m_NmbrLives(3)
{
}

void tyr::PlayerHealthComp::Initialize()
{
}
void tyr::PlayerHealthComp::LoseHealth()
{
	m_NmbrLives--;

	std::for_each(m_pOnHealthChangedFunctions.begin(), m_pOnHealthChangedFunctions.end(), [&](std::function<void(int)>* pFunc)
		{
			if ((*pFunc))
				(*pFunc)(m_NmbrLives);
		});
}

void tyr::PlayerHealthComp::AddOnHealthChangedFunction(std::function<void(int)>* func)
{
	auto found = std::find_if(m_pOnHealthChangedFunctions.begin(), m_pOnHealthChangedFunctions.end(), [&func](auto f) {return f == func; });
	if (found == m_pOnHealthChangedFunctions.end())
		m_pOnHealthChangedFunctions.emplace_back(func);
}

void tyr::PlayerHealthComp::RemoveOnHealthChangedFunction(std::function<void(int)>* func)
{
	auto found = std::find_if(m_pOnHealthChangedFunctions.begin(), m_pOnHealthChangedFunctions.end(), [&func](auto f) {return f == func; });
	if (found != m_pOnHealthChangedFunctions.end())
		m_pOnHealthChangedFunctions.erase(found);
}
#ifdef EDITOR_MODE


void tyr::PlayerHealthComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);	
}

void tyr::PlayerHealthComp::InternalRenderEditor()
{
}
#endif
