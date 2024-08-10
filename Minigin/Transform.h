#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "BaseComponent.h"

namespace dae
{
	class GameActor;
	class Transform final
	{
	public:
		Transform();
		virtual ~Transform() = default;

		void SetWorldPosition(const glm::vec3 worldPos);
		const glm::vec3& GetWorldPosition() const { return m_WorldPos; }
		void SetLocalPosition(const glm::vec3 localPos);
		const glm::vec3& GetLocalPosition() const { return m_LocalPos; }

		void Translate(const glm::vec3& translation);
		void Rotate(const float angle);
		void LookAt(const glm::vec3& target);

		Transform(const Transform&) = delete;
		Transform(Transform&&) = delete;
		Transform& operator=(const Transform&) = delete;
		Transform& operator=(const Transform&&) = delete;
	private:
		glm::vec3 m_LocalPos;
		glm::vec3 m_WorldPos;
		glm::vec3 m_LookAt;
		glm::vec3 m_Scale;
		glm::vec3 m_Speed;
	};
}
