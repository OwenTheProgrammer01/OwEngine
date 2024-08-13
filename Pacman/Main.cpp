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
}

int main(int, char* []) {
	dae::Minigin engine("../Data/", "Pacman");
	engine.Run(load);
	return 0;
}