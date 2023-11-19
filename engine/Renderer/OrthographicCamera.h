
// Luhao 2023.11.19

#pragma once

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

namespace Nova {
	class OrthographicCamera {
	public:
		OrthographicCamera(float left, float right, float bottom, float top)
			// ʹ�� glm ������һ����������
			: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
		{
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

		const glm::vec3& GetPosition() const { return m_Position; }

		void SetPosition(const glm::vec3& position) {
			m_Position = position;
			RecalculateViewMatrix();
		}

		float GetRotation() const { return m_Rotation; }
		void SetRotation(float rotation) {
			m_Rotation = rotation;
			RecalculateViewMatrix();
		}

		inline const glm::mat4& GetProjectionMatrix() const { return m_ProjectionMatrix; }
		inline const glm::mat4& GetViewMatrix() const { return m_ViewMatrix; }
		inline const glm::mat4& GetViewProjectionMatrix() const { return m_ViewProjectionMatrix; }

		void RecalculateViewMatrix() {
			// ���¼��� view ����
			glm::mat4 transform = glm::translate(glm::mat4(1.0f), m_Position) *
				glm::rotate(glm::mat4(1.0f), glm::radians(m_Rotation), glm::vec3(0, 0, 1));
			m_ViewMatrix = glm::inverse(transform);
			m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
		}

	private:
		// MVP�任 * https://luhao.wiki/posts/30P8RVY/
		glm::mat4 m_ProjectionMatrix;  // Proj �任
		glm::mat4 m_ViewMatrix;        // View �任
		glm::mat4 m_ViewProjectionMatrix;

		glm::vec3 m_Position = { 0.0f, 0.0f, 0.0f };
		float m_Rotation = 0.0f;
	};
}
