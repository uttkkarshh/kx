#pragma once
#include "Core.h"
#include <utility>
namespace kx {
	class kx_API Input {
	public:
		static bool IsKeyPressed(int KeyCode) { return s_Instance->IsKeyPressedImpl(KeyCode); }

		inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
		inline static std::pair<float, float> GetMousePosition() { return s_Instance->GetMousePositionImpl(); }
		inline static float GetMouseX() { return s_Instance->GetMouseXImpl(); }
		inline static float GetMouseY() { return s_Instance->GetMouseYImpl(); }
	protected:
	
		virtual bool IsKeyPressedImpl(int keyCode) = 0;
		virtual bool IsMouseButtonPressedImpl(int button) = 0;
		virtual std::pair<float, float> GetMousePositionImpl() = 0;
		virtual float GetMouseXImpl() = 0;
		virtual float GetMouseYImpl() = 0;
	private: 
		static Input* s_Instance;
	};






}
