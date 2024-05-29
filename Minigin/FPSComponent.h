#pragma once
#include "BaseComponent.h"

namespace dae
{
	class GameActor;
	class TextComponent;
	class FPSComponent : public BaseComponent
	{
	public:
		void Update() override;

		FPSComponent(GameActor* pOwner);
		virtual ~FPSComponent() = default;
		FPSComponent(const FPSComponent& other) = delete;
		FPSComponent(FPSComponent&& other) = delete;
		FPSComponent& operator=(const FPSComponent& other) = delete;
		FPSComponent& operator=(FPSComponent&& other) = delete;
	private:
		int m_FrameCount;
		float m_AccumulatedTime;
		float m_MaxTime{ 1.f };

		TextComponent* m_pTextComp;
	};
}
