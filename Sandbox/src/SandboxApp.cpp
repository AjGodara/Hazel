#include "hzpch.h"
#include "Hazel.h"

class ExampleLayer : public Hazel::Layer
{
public:
	ExampleLayer() :Layer("ExampleLayer")
	{

	}

	void OnUpdate() override
	{
		//HZ_INFO("ExampleLayer::Update");
		if (Hazel::Input::IsKeyPressed(HZ_KEY_TAB))
			HZ_TRACE("TAB key pressed");
	}

	void OnEvent(Hazel::Event& event) override
	{
		//HZ_TRACE("{0}", event);
		if (event.GetEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			if (e.GetKeyCode() == HZ_KEY_RIGHT_SHIFT)
				HZ_TRACE("Right Shift pressed");

			HZ_TRACE("{0}", (char)e.GetKeyCode());
		}
	}
};

class Sandbox : public Hazel::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Hazel::ImGuiLayer());
	}
	~Sandbox()
	{

	}
	
};

Hazel::Application* Hazel::CreateApplication()
{
	return new Sandbox();
}

