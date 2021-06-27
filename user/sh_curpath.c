#include "lib.h"

const char *CURPATH_KEY = "curpath";

void curpath_init(char *path) {
    int r;
    if ((r = syscall_env_var(CURPATH_KEY, path, 0)) < 0) user_panic("Init curpath failed: %d.", r);
}

int curpath_get(char *path) {
    int r;
    if ((r = syscall_env_var(CURPATH_KEY, path, 1)) < 0) return r;
}

int curpath_set(char *path) {
    int r;
    if ((r = syscall_env_var(CURPATH_KEY, path, 2)) < 0) return r;
}

int curpath_get_parent(char *path) {
    int r, i;
    if ((r = curpath_get(path)) < 0) return r;
    if (strlen(path) == 1) return 0;

    for (i = strlen(path) - 2; path[i - 1] != '/'; i--);
    path[i] = 0;
}

int curpath_extend(char *path) {
}
