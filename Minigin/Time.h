#pragma once
#include <chrono>

#include "Singleton.h"

using namespace std::chrono;

namespace dae
{
	class Time final : public Singleton<Time>
	{
	public:
		void Update();
		void ProcessLag() { m_Lag -= m_FixedTimeStep; }

		float GetDeltaTime() const { return m_DeltaTime; }
		float GetFixedTimeStep() const { return m_FixedTimeStep; }
		auto GetSleepTime() const { return (m_LastTime + milliseconds(m_MsPerFrame) - high_resolution_clock::now()); }
		bool IsLag() const { return m_Lag >= m_FixedTimeStep; }

		~Time() = default;
		Time(const Time& other) = delete;
		Time(Time&& other) = delete;
		Time& operator=(const Time& other) = delete;
		Time& operator=(Time&& other) = delete;
	private:
		friend class Singleton<Time>;
		Time() = default;

		high_resolution_clock::time_point m_LastTime{ high_resolution_clock::now() };
		float m_DeltaTime{ 0.f };
		float m_Lag{ 0.f };
		float m_FixedTimeStep{ 0.02f };
		int m_FPS{ 60 };
		long m_MsPerFrame{ (1000 / m_FPS) };
	};
}