
// Luhao 2023.11.18

#include "Application.h"
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>
#include "ImGuiLayer.h"
#include "imgui_impl_glfw.h"
#include "tracy/Tracy.hpp"

namespace Nova {
	void ImGuiLayer::OnAttach() {
		LOG_INFO("{}::OnAttach", m_DebugName);
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO io = ImGui::GetIO();
		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		// 开启 docking 模式（可拖动的自由布局窗口）
		io.BackendFlags |= ImGuiConfigFlags_DockingEnable;
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;

		const auto& ints = Application::Instance();

		ImGui_ImplGlfw_InitForOpenGL((GLFWwindow*)Application::Instance().GetWindow().GetNativeWindow(), true);
		ImGui_ImplOpenGL3_Init("#version 330");
	}

	void ImGuiLayer::OnDetach() {
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin() {
		ZoneScopedN("ImGuiLayer_Begin");
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End() {
		ZoneScopedN("ImGuiLayer_End");
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Instance();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::ShowDemoWindow() {
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
	}
}