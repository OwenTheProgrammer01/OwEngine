#pragma once
#include <memory>

#include "Action.h"

namespace dae
{
    class Device abstract
    {
    public:
        Device() = default;
        virtual ~Device() = default;

        virtual void ProcessInput() = 0;

        Device(const Device&) = delete;
        Device(Device&&) = delete;
        Device& operator=(const Device&) = delete;
        Device& operator=(const Device&&) = delete;
    };
}
