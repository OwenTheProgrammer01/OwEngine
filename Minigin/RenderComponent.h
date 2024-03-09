#include "BaseComponent.h"
#include <memory>
#include "transform.h"

namespace dae
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		void Update() override;

		void Render() const;
		void SetTexture(const std::string& filename);

		RenderComponent(GameObject* pOwner);
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	private:
		// todo: Transform&
		Transform m_transform; 
		std::shared_ptr<Texture2D> m_texture{};
	};
}
