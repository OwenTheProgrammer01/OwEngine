#include "Component.h"

namespace dae
{
	class Texture2D;
	class RenderComponent : public Component
	{
	public:
		void Update() override;
		void Render() const;

		RenderComponent();
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	};
}