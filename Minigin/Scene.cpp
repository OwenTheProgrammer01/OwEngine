#include "Scene.h"
#include "GameActor.h"
#include "TrashTheCache.h"

#include <algorithm>

namespace dae
{
	unsigned int Scene::m_idCounter = 0;

	Scene::Scene(const std::string& name) : m_name(name) {}

	Scene::~Scene() = default;

	void Scene::Add(std::shared_ptr<GameActor> actor)
	{
		m_objects.emplace_back(std::move(actor));
	}

	void Scene::Remove(std::shared_ptr<GameActor> actor)
	{
		m_objects.erase(std::remove(m_objects.begin(), m_objects.end(), actor), m_objects.end());
	}

	void Scene::RemoveAll()
	{
		m_objects.clear();
	}

	void Scene::Update()
	{
		for (auto& object : m_objects)
		{
			object->Update();
		}
	}

	void Scene::Render() const
	{
		for (const auto& object : m_objects)
		{
			object->Render();
		}
	}

	void Scene::RenderUI() const
	{
		// Begin of my widgets code
		//TrashTheCache::GetInstance().Exercise1();
		//TrashTheCache::GetInstance().Exercise2();
		// End of my widgets code
	}
}