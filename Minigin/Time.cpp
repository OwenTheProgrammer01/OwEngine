#include "Time.h"

void dae::Time::Update()
{
	const auto currentTime{ high_resolution_clock::now() };
	m_DeltaTime = duration<float>(currentTime - m_LastTime).count();

	m_LastTime = currentTime;
	m_Lag += m_DeltaTime;
}