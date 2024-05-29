#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

namespace dae
{
	class GameActor;

	class Transform final
	{
	public:
		Transform(GameActor* pGameObject);

		void SetPosition(float x, float y, float z);
		const glm::vec3& GetPosition() const { return m_position; }

		void Rotate(float angle, const glm::vec3& axis, bool rotateAroundParent = true, const glm::vec3& rotPoint = {});
	private:
		GameActor* m_pGameObject;
		glm::vec3 m_position;
	};
}
