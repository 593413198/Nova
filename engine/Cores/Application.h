
// Luhao 2023.11.18

#pragma once

#include <memory>
#include "Window.h"
#include "Log.h"
#include "Event.h"
#include "ApplicationEvent.h"
#include "Layer.h"
#include "LayerStack.h"
#include "ImGui/ImGuiLayer.h"

namespace Nova {
class Application {
public:
	Application();
	virtual ~Application();
	void Run();

	void OnEvent(Event& e);
	bool OnWindowClose(WindowCloseEvent& e);

	void PushLayer(Layer* layer);

	inline Window& GetWindow() {
		return *m_Window;
	}

	inline static Application& Instance() {
		return *s_Instance;
	}

private:
	std::unique_ptr<Window> m_Window;
	bool m_Running = true;
	LayerStack m_LayerStack;
	ImGuiLayer* m_ImGuiLayer;

private:
	static Application* s_Instance;
};

Application* CreateApplication();
}

