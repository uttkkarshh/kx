#include "kx.h"

class sand : public kx::Application {
public:
	sand() {

	}
	~sand() {

	}
};
kx::Application* kx::CreateApplication() {
	return  new sand;

}