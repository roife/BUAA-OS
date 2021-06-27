#include "lib.h"

void history_init() {
    int r;
    if ((r = create("/.history", FTYPE_REG)) < 0) user_panic("Init .history failed: %d.", r);
}

void history_save(char *s) {
    int r;
    if ((r = open("/.history", O_RDWR | O_CREAT | O_APP)) < 0) user_panic("Open .history failed");
    fwritef(r, s);
    fwritef(r, "\n");
    close(r);
}

int history_read(char (*cmd)[128]) {
    int r, fd, cur = 1;
    char buf[128 * 128];
    if ((fd = open("/.history", O_RDONLY)) < 0) user_panic("Open .history failed");
    if ((r = read(fd, buf, (long) sizeof buf)) < 0) {
        user_panic("Read .history failed");
    }
    close(fd);

    int i = 0, cmdi = 0;
    while (buf[i]) {
        int cmdj = 0;
        while (buf[i] && buf[i] != '\n') cmd[cmdi][cmdj++] = buf[i++];
        if (!buf[i]) break;
        ++i;
        ++cmdi;
    }
    return cmdi;
}
