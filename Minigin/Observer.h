#pragma once
#include <memory>
#include <string>
#include <functional>
#include <map>
#include "GameActor.h"

namespace dae
{
	class Observer abstract
	{
	public:
		Observer() = default;
		virtual ~Observer() = default;

		virtual void Notify(GameActor* actor, Event event) = 0;

		Observer(const Observer&) = delete;
		Observer(Observer&&) = delete;
		Observer& operator=(const Observer&) = delete;
		Observer& operator=(const Observer&&) = delete;
	};
}