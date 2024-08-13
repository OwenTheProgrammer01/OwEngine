#include "PlayerComponent.h"
#include "InputManager.h"
#include "GameAction.h"
#include "GameTime.h"
#include "LevelManager.h"

PlayerComponent::PlayerComponent(dae::GameActor* pOwner)
	: dae::BaseComponent(pOwner), m_Speed(48.0f)
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

	pOwner->SetSpeed(m_Speed);
}

void PlayerComponent::Update()
{
	auto& levelManager = LevelManager::GetInstance();
	auto newPos = GetOwner()->GetWorldPosition() + dae::GameTime::GetInstance().GetDeltaTime() * GetOwner()->GetTranslation() * m_Speed;

	//if (IsCollidingWithWall(newPos, levelManager.GetWallPositions())) 
	//{
	//	GetOwner()->SetWorldPosition(GetOwner()->GetWorldPosition());
	//}
	//else
	//{
	//	// Update player position if no collision
	//	GetOwner()->Translate(GetOwner()->GetTranslation());
	//}

	if (!IsCollidingWithWall(newPos, levelManager.GetWallPositions()))
	{
		// Update player position if no collision
		GetOwner()->Translate(GetOwner()->GetTranslation());
	}
}

void PlayerComponent::Render() const
{
	
}

bool PlayerComponent::IsCollidingWithWall(const glm::vec3& newPos, const std::vector<glm::vec3>& wallPositions) {
	for (const auto& wallPos : wallPositions) {
		if (glm::distance(newPos, wallPos) < 15.5f) {
			return true;
		}
	}
	return false;
}