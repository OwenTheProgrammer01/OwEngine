#include "LevelBlock.h"
#include "Scene.h"
#include "GameActor.h"
#include "RenderComponent.h"

LevelBlock::LevelBlock(const std::string& type, const glm::vec3& worldPos)
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("LevelBlock");

	auto gaBlock = std::make_shared<dae::GameActor>();
	auto rcBlock = std::make_shared<dae::RenderComponent>(gaBlock.get());
	rcBlock->SetTexture("Sprites/" + type + ".png");
	gaBlock->AddComponent(rcBlock);
	gaBlock->SetWorldPosition(worldPos);
	scene.Add(gaBlock);
}