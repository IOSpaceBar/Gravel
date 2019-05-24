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
   
   //MARKER: MENU VALUES
   int menu1 = 2;
   int menu2 = 3;
   int current = 2;
   printf("GRAVEL by IOSpaceBar\n");
   //MARKER RENDER MENU
   printf("\n\x1b[2;4HInstall");
   printf("\n\x1b[3;4HExit");
   printf("\x1b[%d;2H>", current);
   
    while(appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);
		//MARK: MENU MOVE CODE
		if (kDown & KEY_UP) 
		{
			printf("\x1b[%d;2H ", current);
			current = current - 1;
			if (current < 2) current = 3;
				printf ("\n");
			    printf ("\x1b[%d;2H>", current);		
			}

			if (kDown & KEY_DOWN) {
				printf("\x1b[%d;2H ", current);
			current = current + 1; 
			if (current > 3) current = 2;
				printf("\n");
				printf("\x1b[%d;2H>", current);
		}
		//MARK: MENU ENTER SELECTION CODE
		if(kDown & KEY_A & current == 2){
			//TODO: INSTALL MENU
		}
		if(kDown & KEY_A & current == 3){
			//NOTE: DOING "BREAK;" EXITS THE MAIN LOOP ESSENTIALLY CLOSING THE PROGRAM.
			break;
		}
        if (kDown & KEY_PLUS) break;

        consoleUpdate(NULL);
    }

    consoleExit(NULL);
	splExit();
	romfsExit();
    return 0;
}
