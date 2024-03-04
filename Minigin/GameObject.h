#pragma once
#include <memory>
#include "Transform.h"
#include <vector>
#include "BaseComponent.h"
#include <type_traits>

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

		void SetTexture(const std::string& filename);
		void SetPosition(float x, float y);
		
		//Components
		template<typename T>
		void AddComponent(T&& component) requires ComponentConcept<T>
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

		GameObject() = default;
		virtual ~GameObject();
		GameObject(const GameObject& other) = delete;
		GameObject(GameObject&& other) = delete;
		GameObject& operator=(const GameObject& other) = delete;
		GameObject& operator=(GameObject&& other) = delete;
	private:
		Transform m_transform{};
		// todo: mmm, every gameobject has a texture? Is that correct?
		std::shared_ptr<Texture2D> m_texture{};

		std::vector<std::shared_ptr<BaseComponent>> m_components;
	};
}
