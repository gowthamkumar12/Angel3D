#include "Angel3D.h"

class Sandbox : public Angel3D::Core::Application
{
	public:
		Sandbox()
		{
			PushOverlay(new Angel3D::ImGuiImpl::ImGuiLayer());
		}

		~Sandbox()
		{

		}
};

Angel3D::Core::Application* Angel3D::Core::CreateApplication()
{
	return new Sandbox();
}