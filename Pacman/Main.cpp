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

	//---------- (Sound System) ----------
	std::unique_ptr<dae::ISoundSystem> soundSystem = std::make_unique<dae::SDLMixerSS>();
	dae::ServiceLocator::RegisterSoundSystem(std::move(soundSystem));

	//To show that sound works
	input.AddDevice(std::move(std::make_unique<dae::Keyboard>()));
	//
	auto gaSound = std::make_shared<dae::GameActor>();
	//
	auto playSound = std::make_shared<dae::PlaySound>(gaSound.get(), "pacman_beginning.wav");
	auto muteSound = std::make_shared<dae::MuteAllSounds>(gaSound.get());
	auto unmuteSound = std::make_shared<dae::UnmuteAllSounds>(gaSound.get());
	//
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Keys::P, playSound);
	input.BindCommand(dae::State::IsPressed, dae::Keys::M, muteSound);
	input.BindCommand(dae::State::IsPressed, dae::Keys::U, unmuteSound);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/", "Pacman");
	engine.Run(load);
	return 0;
}