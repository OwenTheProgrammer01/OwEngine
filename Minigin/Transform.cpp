#include <cassert>
#include <iostream>

#include "Transform.h"
#include "GameActor.h"

dae::Transform::Transform(GameActor* pOwner)
	: m_pActor(pOwner), m_LocalPos(), m_WorldPos(), m_Rotation(), m_Scale()
{
	assert(m_pActor);
}

void dae::Transform::SetWorldPosition(const glm::vec3 worldPos)
{
    m_WorldPos = worldPos;
}

void dae::Transform::SetLocalPosition(const glm::vec3 localPos)
{
	m_LocalPos = localPos;
}

void dae::Transform::Rotate(float angle, const glm::vec3& axis, bool rotateAroundParent, const glm::vec3& rotPoint)
{
    glm::mat4 rotationMatrix;
    glm::vec4 rotatedOffset;

    assert(!(rotateAroundParent && rotPoint != glm::vec3{}));

    if (rotateAroundParent)
    {
        rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
        rotatedOffset = rotationMatrix * glm::vec4(m_LocalPos, 1.0f);
    }
    else
    {
        glm::mat4 translationMatrix = glm::translate(glm::mat4(1.0f), -rotPoint);
        glm::mat4 reverseTranslationMatrix = glm::translate(glm::mat4(1.0f), rotPoint);

        rotationMatrix = reverseTranslationMatrix * glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis) * translationMatrix;
        rotatedOffset = rotationMatrix * glm::vec4(m_LocalPos, 1.0f);
    }

    m_LocalPos = glm::vec3(rotatedOffset);
    m_pActor->SetPosDirty();
}