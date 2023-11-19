
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
#include "Renderer/Shader.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"

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
	// Shader *https://learnopengl.com/Getting-started/Hello-Triangle
	std::shared_ptr<VertexArray> m_VertexArray;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<Shader> m_Shader;

private:
	static Application* s_Instance;
};

Application* CreateApplication();
}

