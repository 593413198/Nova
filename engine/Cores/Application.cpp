
// Luhao 2023.11.18

#include "Application.h"
#include <glad/glad.h>


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

	Application::Application() {
		PushLayer(new ExampleLayer());
		m_Window = std::unique_ptr<Window>(Window::Create());
		Window::EventCallbackFn fn = std::bind(&Application::OnEvent, this, std::placeholders::_1);
		m_Window->SetEventCallback(fn);
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (m_Running) {
			glClearColor((GLfloat)0.3, (GLfloat)0.3, (GLfloat)0.3, (GLfloat)1.0);
			glClear(GL_COLOR_BUFFER_BIT);
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
	}

	Application* CreateApplication() {
		return new Application();
	}
}
