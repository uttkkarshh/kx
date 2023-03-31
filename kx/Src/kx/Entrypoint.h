#pragma once
#include "Core.h"
#include "Application.h"


	extern kx::Application* kx::CreateApplication();

	int main() {
		auto App = kx::CreateApplication();
		App->Run();
		delete App;
	}
