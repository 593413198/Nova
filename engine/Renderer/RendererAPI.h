
// Luhao 2023.11.19

#pragma once

#include <memory>
#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Nova {

	enum class RendererDeviceType {
		None = 0,
		OpenGL = 1
		// todo: Metal, OpenGL ES, Vulkan
	};

	class RendererAPI {
	public:
		virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;
		virtual void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) = 0;
		inline static RendererDeviceType GetAPI() { return s_API; }

	private:
		static RendererDeviceType s_API;
	};
}
