#include "TesterClass.h"
#include "stdio.h"
#include "Windows.h"
#include "consoleapi.h"

IMAGECPP_API void TestFunction()
{
    AllocConsole();
    FILE* output;
    freopen_s(&output, "CONOUT$", "w", stdout);
    printf("hhi");

}
