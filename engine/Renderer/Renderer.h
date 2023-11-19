
// Luhao 2023.11.19

#pragma once

#include "VertexArray.h"
#include "RendererAPI.h"
#include "OrthographicCamera.h"
#include "Shader.h"

namespace Nova {
	class Renderer {
	public:
		static void BeginScene(OrthographicCamera& camera);
		static void EndScene();

		static void Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererDeviceType GetDeviceType() { return RendererAPI::GetAPI(); }

		// SceneData √Ë ˆ≥°æ∞–≈œ¢
		struct SceneData {
			glm::mat4 ViewProjectionMatrix;
		};

		static SceneData* m_SceneData;
	};
}
