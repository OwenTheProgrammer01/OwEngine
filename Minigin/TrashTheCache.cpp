#include "TrashTheCache.h"
#include "backends/imgui_impl_sdl2.h"
#include "backends/imgui_impl_opengl2.h"
#include "imgui_plot.h"

void dae::TrashTheCache::Exercise1()
{
	// Begin of my widget code
	ImGui::Begin("Exercise 1");
	static int samples = 10;
	ImGui::InputInt("# samples", &samples);
	ImGui::Button("Trash the cache");
	if (ImGui::IsItemClicked())
	{
		ImGui::LabelText("", "Wait for it...");
	}
	ImGui::End();
	// End of my widget code
}

void dae::TrashTheCache::Exercise2()
{

}
