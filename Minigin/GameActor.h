#pragma once
#include <memory>
#include <vector>
#include <type_traits>

#include "Transform.h"
#include "BaseComponent.h"

namespace dae
{
	class Texture2D;

	template<typename T>
	concept ComponentConcept = std::is_base_of_v<BaseComponent, T>;

	class GameActor final
	{
	public:
		GameActor() = default;
		virtual ~GameActor() = default;

		virtual void Update();
		virtual void Render() const;
		
		// ----------- Components -----------
		template<typename T>
		void AddComponent(std::shared_ptr<T> component) requires ComponentConcept<T>
		{
			m_pComponents.emplace_back(component);
		}

		template<typename T>
		void RemoveComponent() requires ComponentConcept<T>
		{
			m_pComponents.erase(std::remove_if(m_pComponents.begin(), m_pComponents.end(),
				[](const auto& component) { return dynamic_cast<T*>(component.get()) != nullptr; }),
				m_pComponents.end());
		}
		
		template<typename T>
		T* GetComponent() const requires ComponentConcept<T>
		{
			for (const auto& component : m_pComponents)
			{
				if (dynamic_cast<T*>(component.get()) != nullptr)
					return dynamic_cast<T*>(component.get());
			}
			return nullptr;
		}

		template<typename T>
		bool HasComponent() const requires ComponentConcept<T>
		{
			return GetComponent<T>() != nullptr;
		}
		// ----------------------------------

		// ----------- Scene Graph -----------
		void SetParent(GameActor* pParent, bool keepWorldPos = false);
		GameActor* GetParent() const { return m_pParent; }
		size_t GetChildCount() { return m_pChildren.size(); }
		GameActor* GetChildAt(unsigned int index) const { return m_pChildren[index]; }

		void SetWorldPosition(const glm::vec3& worldPos);
		const glm::vec3 GetWorldPosition();
		void SetLocalPosition(const glm::vec3& localPos);
		const glm::vec3 GetLocalPosition();
		void Translate(const glm::vec3& translation);
		void Rotate(const float angle);
		void LookAt(const glm::vec3& target);
		void SetPosDirty();
		// -----------------------------------

		void SetDeleteFlag();
		bool GetDeleteFlag() const { return m_DeleteFlag; }

		GameActor(const GameActor& other) = delete;
		GameActor(GameActor&& other) = delete;
		GameActor& operator=(const GameActor& other) = delete;
		GameActor& operator=(GameActor&& other) = delete;
	private:
		std::vector<std::shared_ptr<BaseComponent>> m_pComponents;

		GameActor* m_pParent{};
		std::vector<GameActor*> m_pChildren;

		Transform m_Transform;

		bool m_IsPosDirty = false;

		bool m_DeleteFlag = false;

		void AddChild(GameActor* pChild);
		void RemoveChild(GameActor* pChild);
		bool IsChild(GameActor* pOwner) const;

		void UpdateWorldPosition();
	};
}
