
#pragma once

#include <string>
#include "Renderer/texture.h"

namespace Nova
{
	class OpenGLTexture2D : public Texture2D
	{
	public:
		explicit OpenGLTexture2D(const std::string& path);
		~OpenGLTexture2D() override;

		void GetSize(int& width, int& height) const
		{
			width = m_width;
			height = m_height;
		}

		void Bind(uint32_t slot = 0) const override;

	private:
		std::string m_Path;
		uint32_t m_width, m_height;
		uint32_t m_RendererID;
	};
}
