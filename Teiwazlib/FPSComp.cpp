#include "tyrpch.h"
#include "FPSComp.h"
#include "SceneObject.h"
#include "TyrComps.h"
#include <sstream>

#include "GameContext.h"
#include "Time.h"
#include <iomanip>
#include "BinaryWriter.h"
tyr::FPSComp::FPSComp(const FPSCompType& type, unsigned int textIndex)
	: tyr::BaseComponent(ComponentType::FPS)
	, m_FPSType(type)
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
	if (m_FPSType != FPSCompType::Update) return;
	const auto fps = 1 / m_pSceneObject->GetGameContext()->pTime->deltaTime;
	std::stringstream ss;
	ss << "FPS: " << std::fixed<< std::setprecision(2) << fps;
	
	m_pTextComp->SetText(ss.str());

}

void tyr::FPSComp::FixedUpdate()
{
	if (m_FPSType != FPSCompType::FixedUpdate) return;
	const auto fps = 1 / m_pSceneObject->GetGameContext()->pTime->fixedDeltaTime;
	std::stringstream ss;
	ss << "FPS: " << std::fixed << std::setprecision(2) << fps;

	m_pTextComp->SetText(ss.str());
}

void tyr::FPSComp::Render() const
{
}
#ifdef EDITOR_MODE
void tyr::FPSComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	
	writer.Write(m_FPSType);
	writer.Write(m_TextIndex);
	
}
#endif

