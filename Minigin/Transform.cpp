#include <cassert>
#include <iostream>

#include "Transform.h"
#include "GameActor.h"
#include "GameTime.h"

dae::Transform::Transform()
	: m_LocalPos(), m_WorldPos(), m_LookAt(), m_Scale(), m_Speed(100.f), m_Translation()
{}

void dae::Transform::SetWorldPosition(const glm::vec3 worldPos)
{
    m_WorldPos = worldPos;
}

void dae::Transform::SetLocalPosition(const glm::vec3 localPos)
{
	m_LocalPos = localPos;
}

void dae::Transform::Translate(const glm::vec3& translation)
{
    m_Translation = translation;
    SetWorldPosition(GetWorldPosition() + GameTime::GetInstance().GetDeltaTime() * translation * m_Speed);
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