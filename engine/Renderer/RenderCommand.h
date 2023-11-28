
// Luhao 2023.11.19

#include "RendererAPI.h"
#include "tracy/Tracy.hpp"

namespace Nova {
	class RenderCommand {
	public:
		static inline void SetClearColor(const glm::vec4& color) {
			s_RendererAPI->SetClearColor(color);
		};
		static inline void Clear() {
			s_RendererAPI->Clear();
		}
		static inline void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
			ZoneScopedN("RenderCommnad_DrawIndexed");
			s_RendererAPI->DrawIndexed(vertexArray);
		}

	private:
		static RendererAPI* s_RendererAPI;
	};
}

