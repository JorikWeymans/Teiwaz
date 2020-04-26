#include "stdafx.h"
#include "ReadScene.h"
#include "ContentManager.h"
#include "BinStructureHelpers.h"
#include "TyrException.h"
#include <sstream>
#include "BinaryReader.h"
#include "Factory.h"
#include "SceneObject.h"
#include "TyrComps.h"

bub::ReadScene::ReadScene()
	: tyr::Scene("Read from file",
		"./Data/Scenes/Read from file.tyrScene")
{
}

