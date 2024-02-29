#include <string>
#include "GameObject.h"
#include "ResourceManager.h"
#include "Renderer.h"

dae::GameObject::~GameObject() = default;

void dae::GameObject::Update(){}

void dae::GameObject::Render() const
{
	const auto& pos = m_transform.GetPosition();
	Renderer::GetInstance().RenderTexture(*m_texture, pos.x, pos.y);
}

void dae::GameObject::SetTexture(const std::string& filename)
{
	m_texture = ResourceManager::GetInstance().LoadTexture(filename);
}

void dae::GameObject::SetPosition(float x, float y)
{
	m_transform.SetPosition(x, y, 0.0f);
}

void dae::GameObject::AddComponent(BaseComponent* comp) 
{
    m_components.push_back(comp);
}

void dae::GameObject::RemoveComponent(BaseComponent* comp) 
{
    m_components.erase(std::remove(m_components.begin(), m_components.end(), comp), m_components.end());
    delete comp;
}

dae::BaseComponent* dae::GameObject::GetComponent() 
{
    return nullptr;
}

bool dae::GameObject::HasComponent(BaseComponent* comp)
{
    return std::find(m_components.begin(), m_components.end(), comp) != m_components.end();
}