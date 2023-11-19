
// Luhao 2023.11.18

#include "Renderer/Buffer.h"


namespace Nova {

	// Vertex Buffer
	class OpenGLVertexBuffer : public VertexBuffer {
	public:
		OpenGLVertexBuffer(float* vertices, uint32_t size);
		virtual ~OpenGLVertexBuffer();

		void Bind() const override;
		void Unbind() const override;

	private:
		uint32_t m_RendererID;
	};

	// Index Buffer
	class OpenGLIndexBuffer : public IndexBuffer {
	public:
		OpenGLIndexBuffer(uint32_t* indices, uint32_t count);

		virtual ~OpenGLIndexBuffer();

		void Bind() const override;

		void Unbind() const override;

		uint32_t GetCount() const override { return m_Count; }

	private:
		uint32_t m_RendererID;
		uint32_t m_Count;
	};
}