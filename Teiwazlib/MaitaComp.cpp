#include "tyrpch.h"
#include "MaitaComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
tyr::MaitaComp::MaitaComp()
	:BaseComponent(ComponentType::Maita, "Maita Component")
{
}

tyr::MaitaComp::~MaitaComp()
{
}

void tyr::MaitaComp::Initialize()
{
	//auto pTextureComp = GET_COMPONENT<TextureComp>();
	//if (!pTextureComp) ADD_COMPONENT(new TextureComp(0));
	
	
}

void tyr::MaitaComp::Update()
{
}

#ifdef EDITOR_MODE
void tyr::MaitaComp::Debug()
{
}

void tyr::MaitaComp::InternalRenderEditor()
{
}

void tyr::MaitaComp::Save(BinaryWriter& writer)
{
	UNREFERENCED_PARAMETER(writer);
}
#endif
