#pragma once
#include "Action.h"
#include "GameObject.h"

namespace dae
{
	class GameObjectAction : public Action
	{
	protected:
		GameObject* GetGameObject() const { return m_Object; }
	public:
		GameObjectAction(GameObject* object) : m_Object(object) {}
		virtual ~GameObjectAction() = default;
	private:
		GameObject* m_Object;
	};

	class Movement final : public GameObjectAction {
	public:
		//Movement() = default;
		//~Movement() override = default;

		void Execute() override
		{
			//GetGameObject()->GetComponent<>()
		}

		//Movement(const Movement&) = delete;
		//Movement& operator=(const Movement&) = delete;
		//Movement(Movement&&) = delete;
		//Movement& operator=(Movement&&) = delete;
	};
}