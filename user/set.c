#include "lib.h"
#include "sh.h"

int flag[256];


void
set(char *name, char *value) {
    int r;

    if ((r = syscall_env_var(name, value, 2)) < 0) {
        if (r == -13) syscall_env_var(name, value, 0);
        else if (r == -14) fwritef(1, "set: [%s] is readonly\n", name);
        return;
    }
}

void
set_readonly(char *name, char *value) {
    int r;

    if ((r = syscall_env_var(name, value, 2)) < 0) {
        if (r == -13) syscall_env_var(name, value, 5);
        else if (r == -14) fwritef(1, "set: [%s] is readonly\n", name);
        return;
    }
}

void
usage(void) {
    fwritef(1, "usage: set [var] [value]\n");
    exit();
}

void
umain(int argc, char **argv) {
    int i;
    ARGBEGIN
    {
        default:
            usage();
        case 'r':
            flag[(u_char) ARGC()]++;
        break;
    }
    ARGEND

    if (argc == 0) return;
    else if (!flag['r']) {
        if (argc == 1) set(argv[0], "");
        else if (argc == 2) set(argv[0], argv[1]);
    } else {
        if (argc == 1) set_readonly(argv[0], "");
        else if (argc == 2) set_readonly(argv[0], argv[1]);
    }
}
