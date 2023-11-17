
// Luhao 2023.11.18

#include "Application.h"
#include <glad/glad.h>

namespace Nova {
	Application::Application() {
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
	}

	bool Application::OnWindowClose(WindowCloseEvent& e) {
		LOG_INFO("Application::OnWindowClose");
		m_Running = false;
		return true;
	}

	Application* CreateApplication() {
		return new Application();
	}
}
