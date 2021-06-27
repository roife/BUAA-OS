#include "lib.h"

int flag[256];


void
touch(char *path, char *prefix) {
    int r, fd;
    char curpath[MAXPATHLEN] = {'\0'};

    if ((r = curpath_get(curpath)) < 0) {
        fwritef(1, "mkdir: cannot get environment var [curpath]\n");
    }

    if (path[0] == '/') {
        // Do Nothing
    } else {
        if (curpath[strlen(curpath) - 1] != '/')
            strcat(curpath, "/");
        strcat(curpath, path);
    }

    if ((r = create(curpath, FTYPE_REG)) < 0) {
        fwritef(1, "File %s Already Exists!\n", curpath);
        return;
    }
    fwritef(1, "File %s created!", curpath);
}

void
usage(void) {
    fwritef(1, "usage: touch [file...]\n");
    exit();
}

void
umain(int argc, char **argv) {
    int i;
    ARGBEGIN
    {
        default:
            usage();
        case 'd':
        case 'F':
        case 'l':
            flag[(u_char) ARGC()]++;
        break;
    }
    ARGEND
    if (argc == 0) {
        return;
    } else {
        for (i = 0; i < argc; i++)
            touch(argv[i], argv[i]);
    }
}
