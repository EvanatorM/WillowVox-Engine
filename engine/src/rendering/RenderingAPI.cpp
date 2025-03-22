#include <WillowVox/rendering/RenderingAPI.h>

#include <WillowVox/rendering/opengl/OpenGLAPI.h>

namespace WillowVox
{
	RenderingAPI* RenderingAPI::m_renderingAPI = nullptr;

	RenderingAPI* RenderingAPI::GetRenderingAPI()
	{
		m_renderingAPI = new OpenGLAPI();
		return m_renderingAPI;
	}
}