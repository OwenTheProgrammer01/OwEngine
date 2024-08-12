#pragma once
//TODO: Finish player class
#include "BaseComponent.h"

class Player final : public dae::BaseComponent
{
public:
	Player() = default;
	~Player() = default;

	void Update() override;
	void Render() const override;

	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& other) = delete;
	Player& operator=(Player&& other) = delete;
};