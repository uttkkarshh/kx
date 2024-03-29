#include "OrthographicCamera.h"
#include "glm/gtc/matrix_transform.hpp"
#include "kx/Debug/Instrumentor.h"

namespace kx {
	OrthographicCamera::OrthographicCamera(float left, float right, float bottom, float top)
		: m_ProjectionMatrix(glm::ortho(left, right, bottom, top, -1.0f, 1.0f)), m_ViewMatrix(1.0f)
	{
		kx_PROFILE_FUNCTION();
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
	void OrthographicCamera::SetProjection(float left, float right, float bottom, float top)
	{
		kx_PROFILE_FUNCTION();
		m_ProjectionMatrix = glm::ortho(left, right, bottom, top, -1.0f, 1.0f);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}

	void OrthographicCamera::RecalculateViewMatrix()
	{
		kx_PROFILE_FUNCTION();
		glm::mat4 traform = glm::translate(glm::mat4(1), m_Position) * glm::rotate(glm::mat4(1),glm::radians( m_Rotation),glm::vec3(0,0,1));
		m_ViewMatrix = glm::inverse(traform);
		m_ViewProjectionMatrix = m_ProjectionMatrix * m_ViewMatrix;
	}
}