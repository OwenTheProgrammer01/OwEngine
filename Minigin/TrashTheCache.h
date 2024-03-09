#pragma once
#include "Singleton.h"

namespace dae
{
	class TrashTheCache final : public Singleton<TrashTheCache>
	{
	public:
		void Exercise1();
		void Exercise2();
	};
}
