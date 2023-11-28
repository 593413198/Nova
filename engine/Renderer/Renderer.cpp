
// Luhao 2023.11.19

#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "tracy/Tracy.hpp"

namespace Nova {
	Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData;

	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}

	void Renderer::EndScene()
	{
	}

	void Renderer::Submit(
		const std::shared_ptr<Shader>& shader,
		const std::shared_ptr<VertexArray>& vertexArray)
	{
		ZoneScopedN("Renderer_Submit");
		shader->Bind();
		// FIXME: Renderer��Ҫ���OpenGL���߼�
		{
			ZoneScopedN("Renderer_UploadUniform");
			std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
			std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));
		}
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}