#pragma once
#include "Command.h"
#include "GameObject.h"

namespace dae
{
	class GameObjectCommand : public Command
	{
	protected:
		GameObject* GetGameObject() const { return m_Object; }
	public:
		GameObjectCommand(GameObject* object) : m_Object(object) {}
		virtual ~GameObjectCommand() = default;
	private:
		GameObject* m_Object;
	};

	class Movement final : public GameObjectCommand {
	public:
		~Movement() override = default;

		void Execute() override
		{
			//GetGameObject()->GetComponent<>()
		}

		Movement(const Movement&) = delete;
		Movement& operator=(const Movement&) = delete;
		Movement(Movement&&) = delete;
		Movement& operator=(Movement&&) = delete;
	};
}