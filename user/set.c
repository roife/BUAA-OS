#include "lib.h"
#include "sh.h"

int flag[256];


void
set(char *name, char *value)
{ 
    int r;

    if((r = syscall_env_var(name, value, 2)) < 0){
        syscall_env_var(name, value, 0);
        return;
    }
}

void
usage(void)
{ 
        fwritef(1, "usage: set [var] [value]\n");
        exit();
} 

void
umain(int argc, char **argv)
{  
    int i;
    if (argc == 0){
        return;    
    }
    else {
        if (argc == 2) set(argv[1], "");
        else if (argc == 3) set(argv[1], argv[2]);
    }
}
