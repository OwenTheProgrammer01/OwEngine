#pragma once

namespace dae
{
    class GameActor;
    class BaseComponent
    {
    public:
        virtual void Update() = 0;
        virtual void FixedUpdate() {};
        virtual void Render() const {};

        virtual ~BaseComponent() = default;
        BaseComponent(const BaseComponent& other) = delete;
        BaseComponent(BaseComponent&& other) = delete;
        BaseComponent& operator=(const BaseComponent& other) = delete;
        BaseComponent& operator=(BaseComponent&& other) = delete;
    private:
        GameActor* m_pOwner;
    protected:
        explicit BaseComponent(GameActor* pOwner) : m_pOwner(pOwner) {}
        GameActor* GetOwner() const { return m_pOwner; }
    };
}
