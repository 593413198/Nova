
// Luhao 2023.11.19

#pragma once

#include "VertexArray.h"
#include "RendererAPI.h"

namespace Nova {
	class Renderer {
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

		inline static RendererDeviceType GetDeviceType() { return RendererAPI::GetAPI(); }
	};
}
