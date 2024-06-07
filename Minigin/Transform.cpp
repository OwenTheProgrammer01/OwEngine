#include <cassert>
#include <iostream>

#include "Transform.h"
#include "GameActor.h"

dae::Transform::Transform()
	: m_LocalPos(), m_WorldPos(), m_LookAt(), m_Scale()
{}

void dae::Transform::SetWorldPosition(const glm::vec3 worldPos)
{
    m_WorldPos = worldPos;
}

void dae::Transform::SetLocalPosition(const glm::vec3 localPos)
{
	m_LocalPos = localPos;
}

void dae::Transform::Rotate(const float angle)
{
    glm::vec3 axis{ 0, 0, 1 };
    glm::mat4 rotationMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    glm::vec3 rotatedPos = rotationMatrix * glm::vec4(m_LocalPos, 1.0f);
    SetLocalPosition(rotatedPos);
}

void dae::Transform::LookAt(const glm::vec3& target)
{
    m_LookAt = target - m_WorldPos;
}

void dae::Transform::LookAt(const float angle)
{
    m_LookAt = glm::vec3(cos(angle), sin(angle), 0);
}