
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

		// ���ɶ�������
		glGenVertexArrays(1, &m_VertexArray);
		// �󶨶�������
		glBindVertexArray(m_VertexArray);

		// ���ɶ��㻺��
		glGenBuffers(1, &m_VertexBuffer);
		// �����黺��
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		// ���������ε�������
		float vertices[3 * 3] = {
				-0.5f, -0.5, 0.0,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f
		};

		// ����������ݡ����������ݰ󶨵�GPU��
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// enable ��һ���������飬��Ӧ shader �еĶ�������
		glEnableVertexAttribArray(0);
		// ���嶥������Ϊ�����㿪ʼ���������ݣ������ͣ������й�һ����ÿ������Ϊ3*float(������)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		// �����������壬���ʶ��ǻ���Ͷ��㻺��û���𣬴治ͬ�����ݶ���
		glGenBuffers(1, &m_IndexBuffer);
		// �󶨵���������
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		// ��������
		unsigned int indices[3] = { 0, 1, 2 };
		//��indices���������������(���͵�GPU)
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (m_Running) {
			glClearColor((GLfloat)0.3, (GLfloat)0.3, (GLfloat)0.3, (GLfloat)1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			glBindVertexArray(m_VertexArray);
			glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

			m_ImGuiLayer->OnUpdate();
			m_Window->OnUpdate();
		}
	}

	void Application::OnEvent(Event& e) {
		LOG_INFO("Application::{}", e.ToString());
		EventDispatcher dispatcher(e);
		// ���� OnWindowClose ���ԣ�����֧�ָ����¼�
		dispatcher.Dispatch<WindowCloseEvent>(std::bind(&Application::OnWindowClose, this, std::placeholders::_1));

		for (const auto& layer : m_LayerStack)
		{
			layer->OnEvent(e);
			// ֻ��͸һ�� layer
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
