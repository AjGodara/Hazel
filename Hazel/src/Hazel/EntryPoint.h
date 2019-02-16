#pragma once

#ifdef HZ_PLATFORM_WINDOWS

extern Hazel::Application* Hazel::CreateApplication();

int main(int argc, char** argv)
{
	printf("Hazel Engine!\n");
	Hazel::Log::Init();
	HZ_CORE_WARN("Initialized Log! ");
	HZ_WARN("Initialized Log! ");
	int a{ 5 };
	HZ_INFO("The variable value is {0}", a);
	
	auto app = Hazel::CreateApplication();
	app->Run();
	delete app;
}
#endif