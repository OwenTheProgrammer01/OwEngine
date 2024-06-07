#pragma once
#include "GameActor.h"

namespace dae
{
	class Observer abstract
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		virtual void Notify(Event event, GameActor* actor) = 0;

		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator=(const Observer&) = delete;
		Observer& operator=(const Observer&&) = delete;
	};
}