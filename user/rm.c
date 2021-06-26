#include "lib.h"

int flag[256];


void
rm(char *path, char *prefix)
{ 
    int r, fd;
    char curpath[MAXPATHLEN] = {'\0'};

    if ((r = curpath_get(curpath)) < 0) {
        fwritef(1, "rm: cannot get environment var [curpath]\n");
    }  

    if(path[0] == '/')
    {
        // Do Nothing
    }
    else
    {
        if(curpath[strlen(curpath) - 1] != '/')
            strcat(curpath, "/");
        strcat(curpath, path);
    }

    if((r = remove(curpath)) < 0){
        fwritef(1, "File %s Not Exists!\n", curpath);
        return;
    }
    fwritef(1, "File %s removed!", curpath);
}

void
usage(void)
{ 
        fwritef(1, "usage: rm [file...]\n");
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
        for (i=0; i<argc; i++)
            rm(argv[i], argv[i]);
    }
}
