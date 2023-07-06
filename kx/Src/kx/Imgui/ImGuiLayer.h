#pragma once
#include "kx/Application.h"
#include "kx/Event/ApplicationEvent.h"
#include "kx/Event/KeyEvent.h"
#include "kx/Event/MouseEvent.h"
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

namespace kx {
	class kx_API ImGuiLayer :public Layer
	{ 
	public: 
		ImGuiLayer();
		~ImGuiLayer();
		virtual void OnUpdate() override;
		virtual void OnEvent (Event& event) override;
		virtual void OnAttach() override;
		virtual void OnDetach() override;
	private :
		bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
		bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
		bool OnMouseMovedEvent(MouseMovedEvent& e);
		bool OnMouseScrolledEvent(MouseScrolledEvent& e);
		bool OnKeyPressedEvent(KeyPressedEvent& e);
		bool OnKeyReleasedEvent(KeyReleasedEvent& e);
		bool OnKeyTypedEvent(KeyTypedEvent& e);
		bool OnWindowResizeEvent(WindowResizeEvent& e);
	private:
		int m_Time;
	};

} 