#include <string>
#include <format>
#include <cassert>

#include "FPSComponent.h"
#include "GameObject.h"
#include "TextComponent.h"
#include "GameTime.h"

dae::FPSComponent::FPSComponent(GameObject* pOwner)
    : BaseComponent(pOwner), m_AccumulatedTime{ 0.f }, m_FrameCount{ 0 }, m_pTextComp{ pOwner->GetComponent<dae::TextComponent>() }
{
    assert(m_pTextComp);
}

void dae::FPSComponent::Update()
{
    m_AccumulatedTime += GameTime::GetInstance().GetDeltaTime();
    ++m_FrameCount;

    if (m_AccumulatedTime >= m_MaxTime)
    {
        const auto txt{ std::format("{:.1f}", m_FrameCount / m_AccumulatedTime) };
        m_pTextComp->SetText(txt + " FPS");

        m_FrameCount = 0;
        m_AccumulatedTime -= m_MaxTime;
    }
}