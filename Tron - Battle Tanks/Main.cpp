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
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	auto& input = dae::InputManager::GetInstance();

	//---------- (Components) ----------
	auto gaBackground = std::make_shared<dae::GameActor>();
	auto rcBackground = std::make_shared<dae::RenderComponent>(gaBackground.get());
	rcBackground->SetTexture("background.tga");
	gaBackground->AddComponent(rcBackground);
	scene.Add(gaBackground);

	auto gaLogo = std::make_shared<dae::GameActor>();
	auto rcLogo = std::make_shared<dae::RenderComponent>(gaLogo.get());
	rcLogo->SetTexture("logo.tga");
	gaLogo->AddComponent(rcLogo);
	gaLogo->SetLocalPosition({ 216, 180, 0 });
	scene.Add(gaLogo);

	auto gaTitle = std::make_shared<dae::GameActor>();
	auto rcTitle = std::make_shared<dae::RenderComponent>(gaTitle.get());
	gaTitle->AddComponent(rcTitle);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tcTitle = std::make_shared<dae::TextComponent>(gaTitle.get(), font);
	tcTitle->SetText("Programming 4 Assignment");
	gaTitle->AddComponent(tcTitle);
	gaTitle->SetLocalPosition({ 80, 20, 0 });
	scene.Add(gaTitle);

	auto gaFPS = std::make_shared<dae::GameActor>();
	auto rcFPS = std::make_shared<dae::RenderComponent>(gaFPS.get());
	gaFPS->AddComponent(rcFPS);
	auto tcFPS = std::make_shared<dae::TextComponent>(gaFPS.get(), font);
	gaFPS->AddComponent(tcFPS);
	auto fcFPS = std::make_shared<dae::FPSComponent>(gaFPS.get());
	gaFPS->AddComponent(fcFPS);
	gaFPS->SetLocalPosition({ 0,0,0 });
	scene.Add(gaFPS);
	//----------------------------------


	//---------- (Scene graph) ----------

	//-----------------------------------


	//---------- (Command & Pimpl) ----------
	input.AddDevice(std::move(std::make_unique<dae::Controller>(0)));
	auto gameActor = std::make_shared<dae::GameActor>();
	auto moveAction = std::make_shared<dae::Movement>(gameActor.get());
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadLeft, moveAction); // Example for controller input
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadRight, moveAction);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadUp, moveAction);
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::DPadDown, moveAction);

	auto shootAction = std::make_shared<dae::Shoot>(gameActor.get());
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::RightShoulder, shootAction);

	auto aimAction = std::make_shared<dae::Aim>(gameActor.get());
	input.BindCommand(dae::State::IsPressedThisFrame, dae::Buttons::LeftShoulder, aimAction);
	//---------------------------------------


	//---------- (Observer & Event queue) ----------


	//----------------------------------------------
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}