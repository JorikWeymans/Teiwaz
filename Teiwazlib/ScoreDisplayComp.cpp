#include "tyrpch.h"
#include "ScoreDisplayComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
#include "GameState.h"
tyr::ScoreDisplayComp::ScoreDisplayComp(int playerNumber)
	:BaseComponent(ComponentType::ScoreDisplay, "ScoreDisplay Component")
	, m_PlayerNmbr(playerNumber)
{
	//Clamp
	if (m_PlayerNmbr != 1 && m_PlayerNmbr != 2)
		m_PlayerNmbr = 1;
}

tyr::ScoreDisplayComp::~ScoreDisplayComp()
{
}

void tyr::ScoreDisplayComp::Initialize()
{
	//auto pTextureComp = GET_COMPONENT<TextureComp>();
	//if (!pTextureComp) ADD_COMPONENT(new TextureComp(0));

	m_pText = GET_COMPONENT<TextComp>();

}
void tyr::ScoreDisplayComp::FixedUpdate()
{
	std::stringstream ss;
	
	ss << "SCORE: ";
	ss << std::to_string(GET_CONTEXT->pGameState->GetScorePlayer1());
	m_pText->SetText(ss.str());
	
}

#ifdef EDITOR_MODE
void tyr::ScoreDisplayComp::Debug()
{
}

void tyr::ScoreDisplayComp::InternalRenderEditor()
{
	std::string name;
	SDXL_ImGui_Text("Player:\t");
	SDXL_ImGui_SameLine();
	name = "##ScoreDisplayCompPlayerID" + std::to_string(m_UniqueId);
	SDXL_ImGui_DragInt(name.c_str(), &m_PlayerNmbr, 1, 1,2);
	
}

void tyr::ScoreDisplayComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_PlayerNmbr);
	UNREFERENCED_PARAMETER(writer);
}
#endif
