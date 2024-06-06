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
#include "TextComponent.h"
#include "FPSComponent.h"

#include "Controller.h"
#include "GameObjectAction.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Tron");
	auto& input = dae::InputManager::GetInstance();

	auto gaPlayer = std::make_shared<dae::GameActor>();
	auto rcPlayer = std::make_shared<dae::RenderComponent>(gaPlayer.get());
	rcPlayer->SetTexture("Sprites/RedTank.png");
	gaPlayer->AddComponent(rcPlayer);
	gaPlayer->SetLocalPosition({ 100,100,0 });
	scene.Add(gaPlayer);

	auto gaEnemy = std::make_shared<dae::GameActor>();
	auto rcEnemy = std::make_shared<dae::RenderComponent>(gaEnemy.get());
	rcEnemy->SetTexture("Sprites/BlueTank.png");
	gaEnemy->AddComponent(rcEnemy);
	gaEnemy->SetParent(gaPlayer.get());
	gaEnemy->SetLocalPosition({ 50,0,0 });
	scene.Add(gaEnemy);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}