
// Luhao 2023/10/30.

#include "test.h"
#include <stdio.h>

namespace Nova {
    void Print()
    {
        Noval::Log::Init();
        LOG_TRACE("test trace log");
        LOG_INFO("test info log");
        LOG_WARN("test warn log");
        LOG_ERROR("test error log");
    }
}