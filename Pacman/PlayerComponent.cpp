#include "PlayerComponent.h"
#include "InputManager.h"
#include "GameAction.h"

PlayerComponent::PlayerComponent(dae::GameActor* pOwner)
	: dae::BaseComponent(pOwner)
{
	auto& input = dae::InputManager::GetInstance();

	input.AddDevice(std::move(std::make_unique<dae::Controller>(0)));
	input.AddDevice(std::move(std::make_unique<dae::Keyboard>()));
	//
	auto moveLeft = std::make_shared<PacmanMovement>(pOwner, glm::vec3(-1, 0, 0));
	auto moveRight = std::make_shared<PacmanMovement>(pOwner, glm::vec3(1, 0, 0));
	auto moveUp = std::make_shared<PacmanMovement>(pOwner, glm::vec3(0, 1, 0));
	auto moveDown = std::make_shared<PacmanMovement>(pOwner, glm::vec3(0, -1, 0));
	//
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadLeft, moveLeft);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadRight, moveRight);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadUp, moveUp);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadDown, moveDown);
	//
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Keys::ArrowLeft, moveLeft);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Keys::ArrowRight, moveRight);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Keys::ArrowUp, moveUp);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Keys::ArrowDown, moveDown);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Keys::A, moveLeft);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Keys::D, moveRight);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Keys::W, moveUp);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Keys::S, moveDown);
}

void PlayerComponent::Update()
{
	GetOwner()->Translate(GetOwner()->GetTranslation());
}

void PlayerComponent::Render() const
{
	
}