#pragma once
#include "Scene.h"
namespace bub
{
	class ReadScene final : public tyr::Scene
	{
	public:
		ReadScene();
		~ReadScene() = default;

	public:
		ReadScene(const ReadScene&) = delete;
		ReadScene(ReadScene&&) = delete;
		ReadScene& operator=(const ReadScene&) = delete;
		ReadScene& operator=(ReadScene&&) = delete;



	};
}
