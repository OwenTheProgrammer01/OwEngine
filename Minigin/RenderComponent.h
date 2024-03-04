#include "BaseComponent.h"

namespace dae
{
	class Texture2D;
	class RenderComponent final : public BaseComponent
	{
	public:
		void Update() override;
		void Render() const override;

		//RenderComponent();
		virtual ~RenderComponent() = default;
		RenderComponent(const RenderComponent& other) = delete;
		RenderComponent(RenderComponent&& other) = delete;
		RenderComponent& operator=(const RenderComponent& other) = delete;
		RenderComponent& operator=(RenderComponent&& other) = delete;
	};
}
