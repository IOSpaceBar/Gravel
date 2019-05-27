#include <string.h>
#include <stdio.h>
#include <switch.h>

void initialize(){
	   //MARK: Initialize console
    consoleInit(NULL);   
	  //MARK: Initialize SPL for system functions
    splInitialize();
}

void updateConsole(int current){
	consoleClear();
	printf("GRAVEL by IOSpaceBar\n");
   	printf("\n\x1b[2;4HInstall");
   	printf("\n\x1b[3;4HExit");
	printf ("\x1b[%d;2H>", current);
}

void generateDirectories(){
    mkdir("/Gravel/", 0700);
	mkdir("/Gravel/packages/", 0700);
	mkdir("/Gravel/header/", 0700);
	fclose(fopen("sdmc:/Gravel/header/header.gravel","w"));
} 

int main(int argc, char **argv)
{
   
   //START: STARTUP OPERATION
	initialize();
	FILE *f = fopen("sdmc:/Gravel/header/header.gravel", "rb");
        if (!f) {
			//NOTE: If the header data (what we use to detect if this is the first time ran on this SD Card) doesnt exist, generate dir's
            generateDirectories();
            
        } else 
			fclose(f);
	//END: STARTUP OPERATION
   
   //MARKER: MENU VALUES
   int current = 2;
   int options = 3;

	updateConsole(current);

    while(appletMainLoop())
    {
        hidScanInput();
        u64 kDown = hidKeysDown(CONTROLLER_P1_AUTO);

		if (kDown & KEY_UP) {
			current += 1;
			if (current > options) {
				current = 2;
			}

			updateConsole(current);
		}
		else if (kDown & KEY_DOWN) {
			current -= 1;
			if (current < options && current == 1) {
				current = options;
			}

			updateConsole(current);
		}
		//MARK: MENU ENTER SELECTION CODE
		if(kDown & KEY_A && current == 2){
			//TODO: INSTALL MENU
		}
		if(kDown & KEY_A && current == 3){
			//NOTE: DOING "BREAK;" EXITS THE MAIN LOOP ESSENTIALLY CLOSING THE PROGRAM.
			break;
		}
        if (kDown & KEY_PLUS) break;

        consoleUpdate(NULL);
    }
	//MARK: EXIT CONSOLE
    consoleExit(NULL);
	//MARK: EXIT SPL
	splExit();
	//MARK: RETURN AKA FINISH EXIT
    return 0;
}
