#include "RenderDevice/RenderDevice.h"

int main (int argc, char **argv)
{
	try
	{
	  stringc arg = argv[0];
	  s32 pos = arg.findLast('/');
	  stringc workDir = arg.subString(0,pos);
	  workDir += L"/";

    for(int i = 0; i < argc; i++)
      printf("Argument %i: %s\n", i, argv[i]);

    printf("Creating render device.\n");
    RenderDevice *g_renderDevice = new RenderDevice();

    printf("Setting working directory.\n");
    g_renderDevice->setWorkDir(workDir);

    printf("Initializing render device.\n");
    g_renderDevice->initialize();

    printf("Entering render loop.\n");
    g_renderDevice->renderLoop();

    if(g_renderDevice)
      delete g_renderDevice;
	}
	catch(char *s)
	{
    #ifdef _WIN32
        MessageBoxA(NULL, s, "Exception thrown", 0);
    #else
        printf("Exception thrown: %s\n", s);
    #endif
	}

	return 0;
}
