
// Luhao 2023.11.18

#include <glad/glad.h>
#include "Application.h"

namespace Nova {

	// * test code begin
	class ExampleLayer : public Layer {
	public:
		ExampleLayer() : Layer("Example") {

		}

		~ExampleLayer() {}

		void OnUpdate() override {
			LOG_INFO("ExampleLayer::Update");
		}

		void OnEvent(Nova::Event& event) override {
			LOG_INFO("ExampleLayer::OnEvent {0}", event.ToString());
		}
	};
	// * test code end

	Application* Application::s_Instance = nullptr;

	Application::Application() {
		s_Instance = this;
		m_Window = std::unique_ptr<Window>(Window::Create());

		//PushLayer(new ExampleLayer());
		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);

		Window::EventCallbackFn fn = std::bind(&Application::OnEvent, this, std::placeholders::_1);
		m_Window->SetEventCallback(fn);
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (m_Running) {
			glClearColor((GLfloat)0.3, (GLfloat)0.3, (GLfloat)0.3, (GLfloat)1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			m_ImGuiLayer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		LOG_INFO("Application::{}", e.ToString());
		EventDispatcher dispatcher(e);
		// 先用 OnWindowClose 测试，后续支持各种事件
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (const auto& layer : m_LayerStack)
		{
			layer->OnEvent(e);
			// 只穿透一层 layer
			if (e.Handled) break;
		}
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		LOG_INFO("Application::OnWindowClose");
		m_Running = false;
		return true;
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	Application* CreateApplication() {
		return new Application();
	}
}
