#include "tyrpch.h"
#include "FPSComp.h"
#include "SceneObject.h"
#include "TyrComps.h"
#include <sstream>

#include "GameContext.h"
#include "Time.h"
#include <iomanip>

tyr::FPSComp::FPSComp(const FPSCompType& type, unsigned int textIndex)
	: tyr::BaseComponent(ComponentType::FPS)
	, m_Type(type)
	, m_pTextComp(nullptr)
	, m_TextIndex(textIndex)
{
}

tyr::FPSComp::~FPSComp()
{
	
	
}

void tyr::FPSComp::Initialize()
{
	m_pTextComp = m_pSceneObject->GetComponent<TextComp>(m_TextIndex);
}

void tyr::FPSComp::Update()
{
	if (m_Type != FPSCompType::Update) return;
	const auto fps = 1 / m_pSceneObject->GetGameContext()->pTime->deltaTime;
	std::wstringstream ss;
	ss << L"FPS: " << std::fixed<< std::setprecision(2) << fps;
	
	m_pTextComp->SetText(ss.str());

}

void tyr::FPSComp::FixedUpdate()
{
	if (m_Type != FPSCompType::FixedUpdate) return;
	const auto fps = 1 / m_pSceneObject->GetGameContext()->pTime->fixedDeltaTime;
	std::wstringstream ss;
	ss << L"FPS: " << std::fixed << std::setprecision(2) << fps;

	m_pTextComp->SetText(ss.str());
}

void tyr::FPSComp::Render() const
{
}
