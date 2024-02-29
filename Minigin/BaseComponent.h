#pragma once

namespace dae
{
    class GameObject;
    class BaseComponent
    {
        GameObject* m_pOwner;
    public:
        virtual void Update() = 0;
        virtual void FixedUpdate() = 0;
        virtual void Render() const;

        virtual ~BaseComponent() = default;
        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;
    protected:
        explicit BaseComponent(GameObject* pOwner) : m_pOwner(pOwner) {}
        GameObject* GetOwner() const { return m_pOwner; }
    };
}
