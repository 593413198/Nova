
// Luhao 2023/10/31

#include "../engine/test.h"

int main()
{
    Nova::Print();
	Noval::Log::Init();
	LOG_TRACE("test trace log");
	LOG_INFO("test info log");
	LOG_WARN("test warn log");
	LOG_ERROR("test error log");
    return 1;
}