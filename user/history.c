#include "lib.h"
#include "sh.h"

char buf[8192];

void
history(int f, char *s) {
    long n;
    int r;

    while ((n = read(f, buf, (long) sizeof buf)) > 0)
        if ((r = write(1, buf, n)) != n)
            user_panic("write error copying %s: %e", s, r);
    if (n < 0)
        user_panic("error reading %s: %e", s, n);
}

void
usage(void) {
    fwritef(1, "usage: history\n");
    exit();
}

void
umain(int argc, char **argv) {
    int f, i;

    writef(LIGHT_CYAN(-- --history-- --\n));
    f = open("/.history", O_RDONLY);
    if (f < 0)
        user_panic("can't open %s: %e", argv[i], f);
    else {
        history(f, argv[i]);
        close(f);
    }
}

