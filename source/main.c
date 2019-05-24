#include <string.h>
#include <stdio.h>
#include <switch.h>
void Initialize(){
	   //MARK: Initialize console
    consoleInit(NULL);   
	  //MARK: Initialize SPL for system functions
    splInitialize();
	 //MARK: Initialize romfs (ROM FILE SYSTEM)
	romfsInit();
	 //MARK: return back to main but with null
	 return;
}

void generateDirectories(){
	//MARK: RESULT = RC (0)
	Result rc = 0;
	//MARK: FILE SYSTEM
    FsFileSystem FS;
    
    if (R_FAILED(rc = fsMountSdcard(&FS)))
    {
        printf("Gravel: Failed to mount the SD File System / !\n");
        return rc;
    }

    mkdir("/Gravel/", 0700);
	mkdir("/Gravel/packages/", 0700);
	mkdir("/Gravel/header/", 0700);
	//CLOSE &FS FOR SAFETY.
	fsFsClose(&FS);
	//MARK: CREATE HEADER DATA 
	FILE *fp;
	fp=fopen("sdmc:/Gravel/header/header.gravel","w");
	fclose(fp);
} 
int main(int argc, char **argv)
{
   
   //START: STARTUP OPERATION
	Initialize();
	FILE *f = fopen("sdmc:/Gravel/header/header.gravel", "rb");
        if (f == NULL) {
			//NOTE: If the header data (what we use to detect if this is the first time ran on this SD Card) doesnt exist, generate dir's
            generateDirectories();
            
        } else {
            //MARK: RETURN
			return;
        }
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
	//MARK: EXIT CONSOLE
    consoleExit(NULL);
	//MARK: EXIT SPL
	splExit();
	//MARK: UNREGISTER ROMFS (ROM FILE SYSTEM)
	romfsExit();
	//MARK: RETURN AKA FINISH EXIT
    return 0;
}
