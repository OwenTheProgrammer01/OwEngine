#pragma once

namespace dae
{
    class Component
    {
    public:
        virtual void Update();

        Component() = default;
        virtual ~Component();
        Component(const Component& other) = delete;
        Component(Component&& other) = delete;
        Component& operator=(const Component& other) = delete;
        Component& operator=(Component&& other) = delete;
    };
}
