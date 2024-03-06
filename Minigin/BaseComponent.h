#pragma once

namespace dae
{
    class GameObject;
    class BaseComponent
    {
    public:
        virtual void Update() = 0;
        virtual void FixedUpdate() {};
        virtual void Render() const = 0;

        virtual ~BaseComponent() = default;
        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;
    private:
        GameObject* m_pOwner;
    protected:
        explicit BaseComponent(GameObject* pOwner) : m_pOwner(pOwner) {}
        GameObject* GetOwner() const { return m_pOwner; }
    };
}
