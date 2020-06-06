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
		AnimationID LoadAnimation(const std::string& animationName);

		void Resize(unsigned int newSize);
		void InsertAt(unsigned int index, Animation* pData) noexcept;

		_NODISCARD Animation* GetAnimation(const std::string& animationName) const;
		_NODISCARD Animation* GetAnimation(AnimationID id) const;
		_NODISCARD AnimationID GetAnimationID(const std::string& animationName) const;
#ifdef EDITOR_MODE
		void RenderEditor();
		void Save(BinaryWriter& writer);
#endif
	private:
		std::vector<Animation*> m_pAnimations;
	public:
		CMAnimations(const CMAnimations&) = delete;
		CMAnimations(CMAnimations&&) = delete;
		CMAnimations& operator=(const CMAnimations&) = delete;
		CMAnimations& operator=(CMAnimations&&) = delete;
	};


}
