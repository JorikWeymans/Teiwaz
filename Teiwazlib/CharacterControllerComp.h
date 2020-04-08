#pragma once
#include "BaseComponent.h"

namespace tyr
{
	class Vector2;
	class CharacterControllerComp final : public BaseComponent
	{
	public:
		explicit CharacterControllerComp();
		~CharacterControllerComp() override;

		void Initialize() override;

		void Update() override;
		void FixedUpdate() override;
		void Render() const override;

		void Move(float x, float y);
		void Move(const Vector2& amount);
	private:
		
	public:
		//CharacterControllerComp() = delete;
		CharacterControllerComp(const CharacterControllerComp&) = delete;
		CharacterControllerComp(CharacterControllerComp&&) = delete;
		CharacterControllerComp& operator=(const CharacterControllerComp&) = delete;
		CharacterControllerComp& operator=(CharacterControllerComp&&) = delete;

	};
}
