#if _DEBUG
// ReSharper disable once CppUnusedIncludeDirective
#if __has_include(<vld.h>)
#include <vld.h>
#endif
#endif

#include "Minigin.h"
#include "Scene.h"
#include "InputManager.h"
#include "ResourceManager.h"

#include "GameActor.h"

#include "RenderComponent.h"
#include "Controller.h"
#include "Keyboard.h"
#include "GameActorAction.h"
#include "EventManager.h"

#include "ServiceLocator.h"
#include "SDLMixerSS.h"

#include "LevelManager.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Pacman");
	auto& input = dae::InputManager::GetInstance();
	auto& levelManager = LevelManager::GetInstance();

	// Load Background
	auto gaBackground = std::make_shared<dae::GameActor>();
	auto rcBackground = std::make_shared<dae::RenderComponent>(gaBackground.get());
	rcBackground->SetTexture("background.tga");
	gaBackground->AddComponent(rcBackground);
	scene.Add(gaBackground);

	//Load Level
	levelManager.LoadLevel("Level");

	auto gaPlayer = std::make_shared<dae::GameActor>();
	auto rcPlayer = std::make_shared<dae::RenderComponent>(gaPlayer.get());
	rcPlayer->SetTexture("Sprites/pacman.png");
	gaPlayer->AddComponent(rcPlayer);
	gaPlayer->SetWorldPosition({ 320,50,0 });
	scene.Add(gaPlayer);

	auto gaEnemy = std::make_shared<dae::GameActor>();
	auto rcEnemy = std::make_shared<dae::RenderComponent>(gaEnemy.get());
	rcEnemy->SetTexture("Sprites/mspacman.png");
	gaEnemy->AddComponent(rcEnemy);
	gaEnemy->SetWorldPosition({ 50,0,0 });
	gaEnemy->SetParent(gaPlayer.get());
	scene.Add(gaEnemy);
	
	//---------- (Command & Pimpl) ----------
	input.AddDevice(std::move(std::make_unique<dae::Controller>(0)));
	input.AddDevice(std::move(std::make_unique<dae::Keyboard>()));
	//
	auto moveLeft = std::make_shared<dae::Movement>(gaPlayer.get(), glm::vec3(-1, 0, 0));
	auto moveRight = std::make_shared<dae::Movement>(gaPlayer.get(), glm::vec3(1, 0, 0));
	auto moveUp = std::make_shared<dae::Movement>(gaPlayer.get(), glm::vec3(0, 1, 0));
	auto moveDown = std::make_shared<dae::Movement>(gaPlayer.get(), glm::vec3(0, -1, 0));
	//
	input.BindCommand(dae::State::IsPressed, dae::Buttons::DPadLeft, moveLeft);
	input.BindCommand(dae::State::IsPressed, dae::Buttons::DPadRight, moveRight);
	input.BindCommand(dae::State::IsPressed, dae::Buttons::DPadUp, moveUp);
	input.BindCommand(dae::State::IsPressed, dae::Buttons::DPadDown, moveDown);
	//
	input.BindCommand(dae::State::IsPressed, dae::Keys::ArrowLeft, moveLeft);
	input.BindCommand(dae::State::IsPressed, dae::Keys::ArrowRight, moveRight);
	input.BindCommand(dae::State::IsPressed, dae::Keys::ArrowUp, moveUp);
	input.BindCommand(dae::State::IsPressed, dae::Keys::ArrowDown, moveDown);
	
	//---------- (Sound System) ----------
	//std::unique_ptr<dae::ISoundSystem> soundSystem = std::make_unique<dae::SDLMixerSS>();
	//dae::ServiceLocator::RegisterSoundSystem(std::move(soundSystem));
}

int main(int, char* []) {
	dae::Minigin engine("../Data/", "Pacman");
	engine.Run(load);
	return 0;
}