#pragma once
#include "Core.h"
#include "Application.h"
#include "Logger.h"
#include "kx/Event/Event.h"
#include "kx/Event/KeyEvent.h"
	

extern kx::Application* kx::CreateApplication();
 

	int main() {
		kx::Logger::Init();
		kx_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Startup.json");
		auto App = kx::CreateApplication();
		kx_PROFILE_END_SESSION();

		kx_PROFILE_BEGIN_SESSION("Runtime", "HazelProfile-Runtime.json");
		App->Run();
		kx_PROFILE_END_SESSION();

		kx_PROFILE_BEGIN_SESSION("Startup", "HazelProfile-Shutdown.json");
		delete App;
		kx_PROFILE_END_SESSION();
	}
