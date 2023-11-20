
// Luhao 2023.11.18

#include <glad/glad.h>
#include "Application.h"
#include "Renderer/Renderer.h"
#include "Renderer/RenderCommand.h"
#include "Input.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "imgui.h"
#include "glm/gtc/type_ptr.hpp"

namespace Nova {

	// * test code begin
	class ExampleLayer : public Layer {
	public:
		ExampleLayer() : Layer("Example") {

		}

		~ExampleLayer() {}

		void OnUpdate() override {
			if (Input::IsKeyPressed(Key::Space))
			{
				LOG_INFO("KeyPressed: Space");
			}
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

		Window::EventCallbackFn fn = std::bind(&Application::OnEvent, this, std::placeholders::_1);
		m_Window->SetEventCallback(fn);

		// 设置 ImGui 图层
		m_ImGuiLayer = new ImGuiLayer();
		PushLayer(m_ImGuiLayer);
		PushLayer(new ExampleLayer());

		m_VertexArray.reset(VertexArray::Create());

		// 矩形，包含uv坐标
		float vertices[5 * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f,
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f
		};

		// vbo
		std::shared_ptr<VertexBuffer> vertexBuffer(VertexBuffer::Create(vertices, sizeof(vertices)));

		// buffer layout
		BufferLayout layout = {
			{ShaderDataType::Float3, "a_Position"},
			{ShaderDataType::Float2, "a_TexCoord"}
			//{ShaderDataType::Float4, "a_Color"},
		};
		vertexBuffer->SetLayout(layout);
		m_VertexArray->AddVertexBuffer(vertexBuffer);

		// index
		unsigned int indices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<IndexBuffer> indexBuffer(IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		// shader
		m_Shader.reset(Shader::Create("../assets/texture.glsl"));
		m_Texture = Texture2D::Create("../assets/demo.png");
		m_Shader->Bind();
		std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformInt("u_Texture", 0);
	}

	Application::~Application() {
	}

	void Application::Run() {
		while (m_Running) {
			RenderCommand::SetClearColor({0.3f, 0.3f, 0.3f, 1.0f});
			RenderCommand::Clear();

			std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->Bind();
			//std::dynamic_pointer_cast<OpenGLShader>(m_Shader)->UploadUniformFloat3("u_Color", m_DebugColor);

			// 模拟 WASD 移动
			{ 
				if (Input::IsKeyPressed(Key::A))
					m_CameraPosition.x -= m_CameraMoveSpeed;
				if (Input::IsKeyPressed(Key::D))
					m_CameraPosition.x += m_CameraMoveSpeed;
				if (Input::IsKeyPressed(Key::W))
					m_CameraPosition.y += m_CameraMoveSpeed;
				if (Input::IsKeyPressed(Key::S))
					m_CameraPosition.y -= m_CameraMoveSpeed;
			}

			// 模拟 QE 二维旋转
			{
				if (Input::IsKeyPressed(Key::Q))
					m_CameraRotation -= m_CameraRotateSpeed;
				if (Input::IsKeyPressed(Key::E))
					m_CameraRotation += m_CameraRotateSpeed;
			}

			// Camera
			m_Camera.SetPosition(m_CameraPosition);
			m_Camera.SetRotation(m_CameraRotation);

			// Scene Render
			Renderer::BeginScene(m_Camera);
			m_Texture->Bind();
			Renderer::Submit(m_Shader, m_VertexArray);
			Renderer::EndScene();

			// ImGui
			m_ImGuiLayer->Begin();
			OnImGuiRender();
			//m_ImGuiLayer->ShowDemoWindow();
			m_ImGuiLayer->End();

			// Windows
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

	void Application::OnImGuiRender() {
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Square Color", glm::value_ptr(m_DebugColor));
		ImGui::End();
	}

	void Application::PushLayer(Layer* layer) {
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}

	Application* CreateApplication() {
		return new Application();
	}
}
