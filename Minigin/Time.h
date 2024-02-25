#pragma once
#include "Singleton.h"

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void SetDeltaTime(float deltaTime);
		float DeltaTime();
	private:
		float m_DeltaTime;
	};
}