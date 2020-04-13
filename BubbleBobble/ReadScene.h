#pragma once
#include "Scene.h"
namespace tyr
{
	class BinaryReader;
	class SceneObject;
}
namespace bub
{
	class BubPrefab;
	class ReadScene final : public tyr::Scene
	{
	public:
		ReadScene();
		~ReadScene() = default;
		void Initialize() override;

	private:
		tyr::SceneObject* LoadSceneObject(tyr::BinaryReader& reader, tyr::SceneObject* parent = nullptr);


	public:
		ReadScene(const ReadScene&) = delete;
		ReadScene(ReadScene&&) = delete;
		ReadScene& operator=(const ReadScene&) = delete;
		ReadScene& operator=(ReadScene&&) = delete;



	};
}
