#pragma once
#include "kx/Layer.h"
#include "kx/Event/ApplicationEvent.h"
#include "kx/Event/KeyEvent.h"
#include "kx/Event/MouseEvent.h"
#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

namespace kx {
	class kx_API ImGuiLayer :public Layer
	{ 
	public: 
		ImGuiLayer();
		~ImGuiLayer();
		
		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		
		void Begin();
		void End();
		
	private:
		int m_Time;
	};

} 