#include <stdio.h>
#include <stdlib.h>

#include "tab_manager.h"

//const char* menu = "welcome\n "

int main()
{
    BROWSER* a_browser;
    char op;
    char tempUrl[512];
    char tempName[40];
    int tempPos;
    a_browser = new_browser();
    
    while(1)
    {
        scanf("%c", &op);
        switch(op)
        {
            case '1':
                //printf("    add tab\n");
                scanf("%s %s", tempName, tempUrl);
                //printf("GOT %s:%s\n", tempName, tempUrl);
                add_tab(a_browser, tempName, tempUrl);
                break;
            case '2':
                //printf("    move_tab\n");
                scanf("%s %d", tempName, &tempPos);
                //printf("GOT %s:%d\n", tempName, tempPos);
                move_tab(a_browser, tempName, tempPos);
                break;
            case '3':   
                //printf("    print tabs\n");
                print_tabs(a_browser);
                break;
            case '4':
                //printf("set me free\n");
                free_browser(a_browser);
                return 0;
                break;
        }
    }

}
