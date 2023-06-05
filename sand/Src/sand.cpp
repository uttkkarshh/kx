#include "kx.h"

class ExampleLayer :public  kx::Layer {
public:
	ExampleLayer() 
		:Layer("From Example Layer")
	{

	}
	void OnUpdate()  override
	{
		kx_CORE_ERROR("Example Layer UPDATE");
	}
	void OnEvent(kx::Event& event)   override {
		kx_CORE_INFO("ON Event");
	}
};

class sand : public kx::Application {
public:
	sand() {
		PushLayer(new ExampleLayer());
	}
	~sand() {

	}
};
kx::Application* kx::CreateApplication() {
	return  new sand;

}