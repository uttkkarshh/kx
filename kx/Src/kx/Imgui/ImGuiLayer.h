#pragma once
#include "kx/Core/Layer.h"
#include "kx/Event/ApplicationEvent.h"
#include "kx/Event/KeyEvent.h"
#include "kx/Event/MouseEvent.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "kx/Core/Logger.h"
namespace kx {
	class kx_API ImGuiLayer :public Layer
	{ 
	public: 
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		
		virtual void OnEvent(Event& e) override;
		void Begin();
		void End();
		void BlockEvents(bool block) { m_BlockEvents = block; 
		kx_CORE_INFO(m_BlockEvents);
		}
	private:
		int m_Time;
		bool m_BlockEvents = true;
	};

} 