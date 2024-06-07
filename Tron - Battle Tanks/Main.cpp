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
#include "GameActorAction.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Tron");
	auto& input = dae::InputManager::GetInstance();

	auto gaPlayer = std::make_shared<dae::GameActor>();
	auto rcPlayer = std::make_shared<dae::RenderComponent>(gaPlayer.get());
	rcPlayer->SetTexture("Sprites/BlueTank.png");
	gaPlayer->AddComponent(rcPlayer);
	gaPlayer->SetWorldPosition({ 320,240,0 });
	scene.Add(gaPlayer);

	auto gaEnemy = std::make_shared<dae::GameActor>();
	auto rcEnemy = std::make_shared<dae::RenderComponent>(gaEnemy.get());
	rcEnemy->SetTexture("Sprites/BlueTank.png");
	gaEnemy->AddComponent(rcEnemy);
	gaEnemy->SetParent(gaPlayer.get());
	gaEnemy->SetLocalPosition({ 50,0,0 });
	gaEnemy->Rotate(50);
	scene.Add(gaEnemy);

	//auto gaEnemy1 = std::make_shared<dae::GameActor>();
	//auto rcEnemy1 = std::make_shared<dae::RenderComponent>(gaEnemy1.get());
	//rcEnemy1->SetTexture("Sprites/BlueTank.png");
	//gaEnemy1->AddComponent(rcEnemy1);
	//gaEnemy1->SetParent(gaPlayer.get());
	//gaEnemy1->SetLocalPosition({ 50,0,0 });
	//gaEnemy1->Rotate(45);
	//scene.Add(gaEnemy1);
	//
	//auto gaEnemy2 = std::make_shared<dae::GameActor>();
	//auto rcEnemy2 = std::make_shared<dae::RenderComponent>(gaEnemy2.get());
	//rcEnemy2->SetTexture("Sprites/BlueTank.png");
	//gaEnemy2->AddComponent(rcEnemy2);
	//gaEnemy2->SetParent(gaPlayer.get());
	//gaEnemy2->SetLocalPosition({ 50,0,0 });
	//gaEnemy2->Rotate(90);
	//scene.Add(gaEnemy2);
	//
	//auto gaEnemy3 = std::make_shared<dae::GameActor>();
	//auto rcEnemy3 = std::make_shared<dae::RenderComponent>(gaEnemy3.get());
	//rcEnemy3->SetTexture("Sprites/BlueTank.png");
	//gaEnemy3->AddComponent(rcEnemy3);
	//gaEnemy3->SetParent(gaPlayer.get());
	//gaEnemy3->SetLocalPosition({ 50,0,0 });
	//gaEnemy3->Rotate(135);
	//scene.Add(gaEnemy3);
	//
	//auto gaEnemy4 = std::make_shared<dae::GameActor>();
	//auto rcEnemy4 = std::make_shared<dae::RenderComponent>(gaEnemy4.get());
	//rcEnemy4->SetTexture("Sprites/BlueTank.png");
	//gaEnemy4->AddComponent(rcEnemy4);
	//gaEnemy4->SetParent(gaPlayer.get());
	//gaEnemy4->SetLocalPosition({ 50,0,0 });
	//gaEnemy4->Rotate(180);
	//scene.Add(gaEnemy4);
	//
	//auto gaEnemy5 = std::make_shared<dae::GameActor>();
	//auto rcEnemy5 = std::make_shared<dae::RenderComponent>(gaEnemy5.get());
	//rcEnemy5->SetTexture("Sprites/BlueTank.png");
	//gaEnemy5->AddComponent(rcEnemy5);
	//gaEnemy5->SetParent(gaPlayer.get());
	//gaEnemy5->SetLocalPosition({ 50,0,0 });
	//gaEnemy5->Rotate(225);
	//scene.Add(gaEnemy5);
	//
	//auto gaEnemy6 = std::make_shared<dae::GameActor>();
	//auto rcEnemy6 = std::make_shared<dae::RenderComponent>(gaEnemy6.get());
	//rcEnemy6->SetTexture("Sprites/BlueTank.png");
	//gaEnemy6->AddComponent(rcEnemy6);
	//gaEnemy6->SetParent(gaPlayer.get());
	//gaEnemy6->SetLocalPosition({ 50,0,0 });
	//gaEnemy6->Rotate(270);
	//scene.Add(gaEnemy6);
	//
	//auto gaEnemy7 = std::make_shared<dae::GameActor>();
	//auto rcEnemy7 = std::make_shared<dae::RenderComponent>(gaEnemy7.get());
	//rcEnemy7->SetTexture("Sprites/BlueTank.png");
	//gaEnemy7->AddComponent(rcEnemy7);
	//gaEnemy7->SetParent(gaPlayer.get());
	//gaEnemy7->SetLocalPosition({ 50,0,0 });
	//gaEnemy7->Rotate(315);
	//scene.Add(gaEnemy7);
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}