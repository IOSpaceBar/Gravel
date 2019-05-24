#include <string.h>
#include <stdio.h>
#include <switch.h>
void Initialize(){
	   //Initialize console
    consoleInit(NULL);   
	  //Initialize SPL for system functions
    splInitialize();
	 //Initialize romfs (ROM FILE SYSTEM)
	romfsInit();
	 //return back to main but with null
	 return;
   }
int main(int argc, char **argv)
{
   
   //START: STARTUP OPERATION
	Initialize();
   //END: STARTUP OPERATION
   
    while(appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

        if (kDown & KEY_PLUS) break;

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
    return 0;
}
