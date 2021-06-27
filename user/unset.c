#include "lib.h"
#include "sh.h"

int flag[256];


void
unset(char *name) {
    int r;

    if ((r = syscall_env_var(name, "", 3)) < 0) {
        fwritef(1, "Environment var " RED([%s]) " Not Exists!\n", name);
        return;
    }
}

void
usage(void) {
    fwritef(1, "usage: unset [vars...]\n");
    exit();
}

void
umain(int argc, char **argv) {
    int i;
    if (argc == 0) {
        return;
    } else {
        for (i = 1; i < argc; i++)
            unset(argv[i]);
    }
}
