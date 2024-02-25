#include "Time.h"

void dae::Time::SetDeltaTime(float deltaTime)
{
	m_DeltaTime = deltaTime;
}

float dae::Time::DeltaTime()
{
	return m_DeltaTime;
}