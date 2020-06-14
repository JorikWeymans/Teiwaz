#include "tyrpch.h"
#include "FoodComp.h"
#include "TyrComps.h"
#include "SceneObject.h"
#include "BinaryWriter.h"
tyr::FoodComp::FoodComp()
	:BaseComponent(ComponentType::Food, "Food Component")
{
}

tyr::FoodComp::~FoodComp()
{
}

void tyr::FoodComp::Initialize()
{


}

void tyr::FoodComp::Update()
{
}

#ifdef EDITOR_MODE
void tyr::FoodComp::Debug()
{
}

void tyr::FoodComp::InternalRenderEditor()
{
}

void tyr::FoodComp::Save(BinaryWriter& writer)
{
	writer.Write(m_Type);
	UNREFERENCED_PARAMETER(writer);
}
#endif
