#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "SceneManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "Scene.h"

#include "GameActor.h"

#include "RenderComponent.h"
#include "Controller.h"
#include "GameActorAction.h"
#include "EventManager.h"

#include "MoveComponent.h"

#include "ServiceLocator.h"
#include "SDLMixerSS.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Tron - Battle Tanks");
	auto& input = dae::InputManager::GetInstance();

	auto gaPlayer = std::make_shared<dae::GameActor>();
	auto rcPlayer = std::make_shared<dae::RenderComponent>(gaPlayer.get());
	rcPlayer->SetTexture("Sprites/RedTank.png");
	gaPlayer->AddComponent(rcPlayer);
	gaPlayer->SetWorldPosition({ 320,240,0 });
	scene.Add(gaPlayer);

	auto gaEnemy = std::make_shared<dae::GameActor>();
	auto rcEnemy = std::make_shared<dae::RenderComponent>(gaEnemy.get());
	rcEnemy->SetTexture("Sprites/BlueTank.png");
	gaEnemy->AddComponent(rcEnemy);
	gaEnemy->SetParent(gaPlayer.get());
	gaEnemy->SetLocalPosition({ 50,0,0 });
	scene.Add(gaEnemy);

	//---------- (Command & Pimpl) ----------
	//input.AddDevice(std::move(std::make_unique<dae::Controller>(0)));
	//auto gameActor = std::make_shared<dae::GameActor>();
	//auto moveAction = std::make_shared<dae::Movement>(gameActor.get());
	//auto moveComponent = std::make_shared<dae::MoveComponent>(gameActor.get());
	//input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadLeft, moveAction);
	//input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadRight, moveAction);
	//input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadUp, moveAction);
	//input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadDown, moveAction);
	//
	//auto shootAction = std::make_shared<dae::Shoot>(gameActor.get());
	//input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::RightShoulder, shootAction);
	//
	//auto aimAction = std::make_shared<dae::Aim>(gameActor.get());
	//input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::LeftShoulder, aimAction);

	//---------- (Sound System) ----------
	//InitializeSoundSystem
	std::unique_ptr<dae::ISoundSystem> soundSystem = std::make_unique<dae::SDLMixerSS>();
	dae::ServiceLocator::RegisterSoundSystem(std::move(soundSystem));
}

int main(int, char* []) {
	dae::Minigin engine("../Data/", "Tron - Battle Tanks");
	engine.Run(load);
	return 0;
}