#include "Angel3D.h"

class ExampleLayer : public Angel3D::Core::Layer
{
	public:
		ExampleLayer()
		: Angel3D::Core::Layer("ExampleLayer")
		{}

		void OnUpdate() override
		{
			if(Angel3D::Core::Input::IsKeyPressed(ANGEL3D_KEY_TAB))
			{
				ANGEL3D_TRACE("Tab key is pressed");
			}
		}

		void OnEvent(Angel3D::Events::Event& f_e)
		{
			if(f_e.GetEventType() == Angel3D::Events::EventType::KeyPressed)
			{
				Angel3D::Events::KeyPressedEvent& e = (Angel3D::Events::KeyPressedEvent&)f_e;
				ANGEL3D_TRACE("{0}", (char)e.GetKeyCode());
			}
		}
};

class Sandbox : public Angel3D::Core::Application
{
	public:
		Sandbox()
		{
		}

		~Sandbox()
		{
		}
};

Angel3D::Core::Application* Angel3D::Core::CreateApplication()
{
	return new Sandbox();
}