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

	class GameObject final
	{
	public:
		virtual void Update();
		virtual void Render() const;
		
		// ----------- Components -----------
		template<typename T>
		void AddComponent(std::shared_ptr<T> component) requires ComponentConcept<T>
		{
			m_components.push_back(component);
		}

		template<typename T>
		void RemoveComponent() requires ComponentConcept<T>
		{
			m_components.erase(std::remove_if(m_components.begin(), m_components.end(),
				[](const auto& component) { return dynamic_cast<T*>(component.get()) != nullptr; }),
				m_components.end());
		}
		
		template<typename T>
		T* GetComponent() const requires ComponentConcept<T>
		{
			for (const auto& component : m_components)
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
		GameObject* GetParent() const;
		void SetParent(GameObject* pParent, bool keepWorldPos = false);
		size_t GetChildCount();
		GameObject* GetChild(size_t idx);
		// -----------------------------------

		void SetLocalPosition(const glm::vec3& pos);
		void SetWorldPosition(float x, float y);

		const glm::vec3& GetWorldPosition();

		void SetPosDirty();

		const Transform& GetTransform() { return m_transform; }

		void SetDeleteFlag();
		
		bool GetDeleteFlag() const { return m_DeleteFlag; }

		GameObject() = default;
		virtual ~GameObject() = default;
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		std::vector<std::shared_ptr<BaseComponent>> m_components;

		Transform m_transform{ this };

		bool m_DeleteFlag = false;

		GameObject* m_pParent;
		std::vector<GameObject*> m_pChildren;

		bool m_PositionIsDirty = false;

		glm::vec3 m_WorldPosition{};

		void UpdateWorldPosition();

		void AddChild(GameObject* pChild);
		void RemoveChild(GameObject* pChild);

		bool IsChild(GameObject* pOwner) const;
	};
}
