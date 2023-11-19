
// Luhao 2023.11.19

#pragma once

namespace Nova {
	enum class RendererDeviceType {
		None = 0, 
		OpenGL = 1
		// todo: Metal, OpenGL ES, Vulkan
	};

	class Renderer {
	public:
		inline static RendererDeviceType GetDeviceType() {
			return s_RendererAPI;
		}
	private:
		static RendererDeviceType s_RendererAPI;
	};
}
