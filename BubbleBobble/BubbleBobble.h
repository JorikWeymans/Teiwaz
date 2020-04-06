#pragma once
#include "Windows.h"
#include "TeiwazEngine.h"
namespace  bub
{
	class BubbleBobble : public tyr::TeiwazEngine
	{
	public:
		BubbleBobble();
		void Initialize(HINSTANCE hinstance);

	protected:
		void LoadGame() override;
		void Cleanup() override;
	};


}
