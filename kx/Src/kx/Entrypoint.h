#pragma once
#include "Core.h"
#include "Application.h"
#include "Logger.h"


	extern kx::Application* kx::CreateApplication();

	int main() {
		kx::Logger::Init();
	
		kx_CORE_WARN("from kx Initialize");
		auto App = kx::CreateApplication();
		App->Run();
		delete App;
	}
