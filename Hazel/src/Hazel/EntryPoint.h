#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	printf("Hazel Engine!\n");
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log!");
	HZ_WARN("Initialized Log!");
	

	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#endif