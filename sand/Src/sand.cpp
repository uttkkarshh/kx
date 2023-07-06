#include "kx.h"

class ExampleLayer :public  kx::Layer {
public:
	ExampleLayer() 
		:Layer("From Example Layer")
	{

	}
	void OnUpdate()  override
	{   
		if (kx::Input::ISKeyPressed(KX_KEY_TAB))
			kx_CORE_INFO("TAB IS PRESSED");


		
	}
	void OnEvent(kx::Event& event)   override {
		//kx_CORE_INFO("ON Event");
	}
};

class sand : public kx::Application {
public:
	sand() {
		PushLayer(new ExampleLayer());
		PushLayer(new kx::ImGuiLayer());
	}
	~sand() {

	}
};
kx::Application* kx::CreateApplication() {
	return  new sand;


}