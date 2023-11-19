
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

		// 生成顶点数组
		glGenVertexArrays(1, &m_VertexArray);
		// 绑定顶点数组
		glBindVertexArray(m_VertexArray);

		// 生成顶点缓冲
		glGenBuffers(1, &m_VertexBuffer);
		// 绑定数组缓冲
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		// 定义三角形的三个点
		float vertices[3 * 3] = {
				-0.5f, -0.5, 0.0,
				0.5f, -0.5f, 0.0f,
				0.0f, 0.5f, 0.0f
		};

		// 填充数组数据。三角形数据绑定到GPU上
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// enable 第一个顶点数组，对应 shader 中的顶点数据
		glEnableVertexAttribArray(0);
		// 定义顶点属性为：从零开始，三组数据，浮点型，不进行归一化，每组数据为3*float(即步幅)
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		// 生成索引缓冲，本质都是缓冲和顶点缓冲没区别，存不同的数据而已
		glGenBuffers(1, &m_IndexBuffer);
		// 绑定到索引缓冲
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);
		// 定义索引
		unsigned int indices[3] = { 0, 1, 2 };
		//将indices填充索引缓冲数据(发送到GPU)
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
