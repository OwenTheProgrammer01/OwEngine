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

#include "GameObject.h"

#include "RenderComponent.h"
#include "TextComponent.h"
#include "FPSComponent.h"

void load()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Demo");
	//auto& input = dae::InputManager::GetInstance();

	//---------- (Components) ----------
	auto goBackground = std::make_shared<dae::GameObject>();
	auto rcBackground = std::make_shared<dae::RenderComponent>(goBackground.get());
	rcBackground->SetTexture("background.tga");
	goBackground->AddComponent(rcBackground);
	scene.Add(goBackground);

	auto goLogo = std::make_shared<dae::GameObject>();
	auto rcLogo = std::make_shared<dae::RenderComponent>(goLogo.get());
	rcLogo->SetTexture("logo.tga");
	goLogo->AddComponent(rcLogo);
	goLogo->SetLocalPosition({ 216, 180, 0 });
	scene.Add(goLogo);

	auto goTitle = std::make_shared<dae::GameObject>();
	auto rcTitle = std::make_shared<dae::RenderComponent>(goTitle.get());
	goTitle->AddComponent(rcTitle);

	auto font = dae::ResourceManager::GetInstance().LoadFont("Lingua.otf", 36);
	auto tcTitle = std::make_shared<dae::TextComponent>(goTitle.get(), font);
	tcTitle->SetText("Programming 4 Assignment");
	goTitle->AddComponent(tcTitle);
	goTitle->SetLocalPosition({ 80, 20, 0 });
	scene.Add(goTitle);

	auto goFPS = std::make_shared<dae::GameObject>();
	auto rcFPS = std::make_shared<dae::RenderComponent>(goFPS.get());
	goFPS->AddComponent(rcFPS);
	auto tcFPS = std::make_shared<dae::TextComponent>(goFPS.get(), font);
	goFPS->AddComponent(tcFPS);
	auto fcFPS = std::make_shared<dae::FPSComponent>(goFPS.get());
	goFPS->AddComponent(fcFPS);
	goFPS->SetLocalPosition({ 0,0,0 });
	scene.Add(goFPS);
	//-----------------------------------------------

	//---------- (Scene graph) ----------


	//------------------------------------------------

	//---------- (Command & Pimple) ----------
	//input.BindActionToKey(dae::ControllerButton::A, dae::KeyState::Pressed, std::make_shared<dae::Movement>());

	//-------------------------------------------------------

	//---------- (Observer & Event queue) ----------


	//----------------------------------------------
}

int main(int, char* []) {
	dae::Minigin engine("../Data/");
	engine.Run(load);
	return 0;
}