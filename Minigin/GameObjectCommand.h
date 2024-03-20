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
		GameObjectCommand(GameObject* object);
		virtual ~GameObjectCommand() = default;
	private:
		GameObject* m_Object;
	};

	class Move final : public GameObjectCommand {
	public:
		void Execute() override
		{
			//GetGameObject()->;
		}
	};
}