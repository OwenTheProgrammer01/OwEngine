#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace dae
{
	class GameActor;

	class Transform final
	{
	public:
		Transform(GameActor* pOwner);
		virtual ~Transform() = default;

		void SetWorldPosition(const glm::vec3 worldPos);
		const glm::vec3& GetWorldPosition() const { return m_WorldPos; }
		void SetLocalPosition(const glm::vec3 localPos);
		const glm::vec3& GetLocalPosition() const { return m_LocalPos; }

		void Rotate(float angle, const glm::vec3& axis, bool rotateAroundParent = true, const glm::vec3& rotPoint = {});

		Transform(const Transform&) = delete;
		Transform(Transform&&) = delete;
		Transform& operator=(const Transform&) = delete;
		Transform& operator=(const Transform&&) = delete;
	private:
		GameActor* m_pActor;

		glm::vec3 m_LocalPos;
		glm::vec3 m_WorldPos;
		glm::vec3 m_Rotation;
		glm::vec3 m_Scale;
	};
}
