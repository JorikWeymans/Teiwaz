#include "tyrpch.h"
#include "AutoDestroyComp.h"
#include "BinaryWriter.h"
#include "SceneObject.h"
#include "GameContext.h"
#include "Time.h"

tyr::AutoDestroyComp::AutoDestroyComp(float lifeTime)
	: BaseComponent(ComponentType::AutoDestroy, "Auto Destroy Component")
	, m_DestroyElapser(lifeTime)
{
}

void tyr::AutoDestroyComp::Update()
{
	if (m_DestroyElapser.Update(TIME->deltaTime))
		m_pSceneObject->Destroy();
}

#ifdef EDITOR_MODE
void tyr::AutoDestroyComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	writer.Write(m_DestroyElapser.GetMax());
}

void tyr::AutoDestroyComp::InternalRenderEditor()
{
	std::string name;


	SDXL_ImGui_Text("LifeTime: ");
	name = "##AutoDestroyComp" + std::to_string(m_UniqueId);

	SDXL_ImGui_SameLine();
	float amount = m_DestroyElapser.GetMax();
	if(SDXL_ImGui_DragFloat(name.c_str(), &amount))
	{
		m_DestroyElapser.Reset(amount);
	}
}
#endif
