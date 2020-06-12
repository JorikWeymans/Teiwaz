#include "tyrpch.h"
#include "ZenChanComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "Time.h"
tyr::ZenChanComp::ZenChanComp()
	:BaseComponent(ComponentType::ZenChan, "ZenChan Component")
{
}

tyr::ZenChanComp::~ZenChanComp()
{
}

void tyr::ZenChanComp::Initialize()
{
	//auto pTextureComp = GET_COMPONENT<TextureComp>();
	//if (!pTextureComp) ADD_COMPONENT(new TextureComp(0));

	//m_pCont = GET_COMPONENT<CharacterControllerComp>();
}

void tyr::ZenChanComp::Update()
{
}

void tyr::ZenChanComp::FixedUpdate()
{
	const float elapsed = TIME->fixedDeltaTime;
	m_pCont->Move(-150 * elapsed, 0);
}

#ifdef EDITOR_MODE
void tyr::ZenChanComp::Debug()
{
}

void tyr::ZenChanComp::InternalRenderEditor()
{
}

void tyr::ZenChanComp::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);
}
#endif
