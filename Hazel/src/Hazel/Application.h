#pragma once

#include "Core.h"

#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"

#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/Shader.h"


namespace Hazel {

	class HAZEL_API Application
	{
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		inline static Application& Get() { return *s_Instance;	}

		void Run();

		inline Window& GetWindow() { return *m_Window; }
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		unsigned int m_VertexArray, m_VertexBuffer, m_IndexBuffer;
		std::unique_ptr<Shader> m_Shader;
	private:
		static Application* s_Instance;

	};

	// To be defined in CLIENT
	Application* CreateApplication();
}
