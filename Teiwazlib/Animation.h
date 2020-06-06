#pragma once
#include "Elapser.h"
#include <vector>
#include "Vectors.h"

namespace tyr
{
	class BinaryWriter;
	class EAnimation;
	typedef std::vector<Rect> SpritePositions;
	
	class Animation final
	{
	public:
		explicit Animation(const std::string& animationName, TextureID spriteID, float tpf, SpritePositions&& sp);
		static Animation* Create(const std::string& path);
		static Animation* GenerateNew(const std::string& name);
		
		~Animation() = default;
		void Update(float elapsed);
		const Rect& GetCurrentAnimation() const;
		void Reset();
		bool IsAtEnd() const { return m_CurrentAnimation == m_AniSprites.size() - 1; }

		const std::string& GetName() const { return m_AnimationName; }
#ifdef EDITOR_MODE
		void Save();
#endif

	private:
		friend bool operator==(Animation* lhs, const std::string& rhs); //rhs == dataPath that gets hashed on creation

		friend EAnimation; //TODO: try to remove friend
		explicit Animation(float tpf);
		Animation();
		
		
		std::string m_AnimationName;
		TextureID m_SpriteID;
		Elapser m_AniElapser;
		unsigned int m_CurrentAnimation;
		SpritePositions m_AniSprites;

	public:
		Animation(const Animation&) = delete;
		Animation(Animation&&) = delete;
		Animation& operator=(const Animation&) = delete;
		Animation& operator=(Animation&&) = delete;



	};


}
