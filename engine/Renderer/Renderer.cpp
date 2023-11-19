
// Luhao 2023.11.19

#include "Renderer.h"
#include "RenderCommand.h"
#include "Platform/OpenGL/OpenGLShader.h"

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
		shader->Bind();
		// FIXME: Renderer��Ҫ���OpenGL���߼�
		std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}
}