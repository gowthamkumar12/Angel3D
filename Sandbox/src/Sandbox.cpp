#include "Angel3D.h"

class ExampleLayer : public Angel3D::Core::Layer
{
	public:
		ExampleLayer()
		: Angel3D::Core::Layer("ExampleLayer")
		{}

		void OnUpdate() override
		{
			ANGEL3D_INFO("ExampleLayer::Updated");
		}

		void OnEvent(Angel3D::Events::Event& f_e) override
		{
			ANGEL3D_INFO("{0}", f_e.ToString());
		}
};

class Sandbox : public Angel3D::Core::Application
{
	public:
		Sandbox()
		{
			PushLayer(new ExampleLayer());
		}

		~Sandbox()
		{

		}
};

Angel3D::Core::Application* Angel3D::Core::CreateApplication()
{
	return new Sandbox();
}