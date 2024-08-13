#pragma once
#include "Action.h"
#include "GameActor.h"
#include "Transform.h"
#include <glm/glm.hpp>
#include "ServiceLocator.h"

namespace dae
{
	class GameActorAction : public Action
	{
	protected:
		GameActor* GetGameObject() const { return m_pOwner; }
	public:
		GameActorAction(GameActor* pOwner) : m_pOwner(pOwner) {}
		virtual ~GameActorAction() = default;
	private:
		GameActor* m_pOwner;
	};

	class Movement final : public GameActorAction {
	public:
		Movement(GameActor* pOwner, const glm::vec3 direction) : GameActorAction(pOwner), m_Direction(direction) 
		{
			m_Direction = glm::normalize(glm::vec3{ direction.x, -direction.y, 0 });
		}
		void Execute() override
		{
			GetGameObject()->Translate(m_Direction);
		}
	private:
		glm::vec3 m_Direction;
	};

	class PlaySound final : public GameActorAction {
	public:
		PlaySound(GameActor* pOwner, const std::string& soundPath) : GameActorAction(pOwner), m_SoundPath(soundPath) {}
		void Execute() override
		{
			ServiceLocator::GetSoundSystem().PlaySound(m_SoundPath, 100);
		}
	private:
		std::string m_SoundPath;
	};

	class MuteAllSounds final : public GameActorAction {
	public:
		MuteAllSounds(GameActor* pOwner) : GameActorAction(pOwner) {}
		void Execute() override
		{
			ServiceLocator::GetSoundSystem().MuteAllSounds(true);
		}
	};

	class UnmuteAllSounds final : public GameActorAction {
	public:
		UnmuteAllSounds(GameActor* pOwner) : GameActorAction(pOwner) {}
		void Execute() override
		{
			ServiceLocator::GetSoundSystem().MuteAllSounds(false);
		}
	};
}