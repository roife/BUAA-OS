#include "lib.h"
#include "sh.h"

char buf[8192];

void
export() {
    char *name_table[1 << 8];
    char *value_table[1 << 8];
    syscall_env_var(name_table, value_table, 4);
    int i = 0;
    while (name_table[i]) {
        fwritef(1, GREEN(%s) " = %s\n", name_table[i], value_table[i]);
        ++i;
    }
}

void
export_i(char *name) {
    char value[256];
    syscall_env_var(name, value, 1);
    fwritef(1, GREEN(%s) " = %s\n", name, value);
}

void
usage(void) {
    fwritef(1, "usage: export\n");
    exit();
}

void
umain(int argc, char **argv) {
    int f, i;

    writef(LIGHT_CYAN(-- --environment variables-- --\n));
    if (argc == 1) export();
    else {
        for (i = 1; i < argc; ++i) export_i(argv[i]);
    }
}

