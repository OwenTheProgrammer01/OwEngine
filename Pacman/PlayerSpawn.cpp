#include "PlayerSpawn.h"
#include "Scene.h"
#include "GameActor.h"
#include "RenderComponent.h"
#include "PlayerComponent.h"

PlayerSpawn::PlayerSpawn(const std::string& character, const glm::vec3& worldPos)
	: LevelBlock("Path", worldPos), m_Character(character), m_WorldPos(worldPos)
{}

void PlayerSpawn::SpawnPlayer()
{
	auto& scene = dae::SceneManager::GetInstance().CreateScene("Player");

	auto gaPlayer = std::make_shared<dae::GameActor>();
	auto rcPlayer = std::make_shared<dae::RenderComponent>(gaPlayer.get());
	rcPlayer->SetTexture("Sprites/" + m_Character + ".png");
	gaPlayer->AddComponent(rcPlayer);
	gaPlayer->SetWorldPosition(m_WorldPos);
	auto pcPlayer = std::make_shared<PlayerComponent>(gaPlayer.get());
	gaPlayer->AddComponent(pcPlayer);
	scene.Add(gaPlayer);
}