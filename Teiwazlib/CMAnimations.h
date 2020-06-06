#pragma once
#include <vector>
namespace tyr
{
	class Animation;
	class BinaryWriter;
	class CMAnimations final
	{
	public:
		CMAnimations() = default;
		~CMAnimations();
		
		void Resize(unsigned int newSize);
		void InsertAt(unsigned int index, Animation* pData) noexcept;

		_NODISCARD Animation*  GetAnimation(const std::string& animationName) const;
		_NODISCARD Animation*  GetAnimation(AnimationID id) const;
		_NODISCARD AnimationID GetAnimationID(const std::string& animationName) const;
#ifdef EDITOR_MODE
		void RenderEditor();
		void Save(BinaryWriter& writer);
#endif
	private:
		std::vector<Animation*> m_pAnimations;
#ifdef EDITOR_MODE
		void ShowAnimations(int& selectedAnimation);

		void BtnDeleteAnimation(int selectedAnimation);
		void BtnMoveAnimationUp(int& selectedAnimation);
		void BtnMoveAnimationDown(int& selectedAnimation);

		void BtnAddAnimation();
#endif

	public:
		CMAnimations(const CMAnimations&) = delete;
		CMAnimations(CMAnimations&&) = delete;
		CMAnimations& operator=(const CMAnimations&) = delete;
		CMAnimations& operator=(CMAnimations&&) = delete;
	};


}
