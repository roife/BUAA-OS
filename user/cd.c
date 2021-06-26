#include "lib.h"
#include "sh.h"

void
usage(void)
{
    fwritef(1, "usage: cd [dir]\n");
    exit();
} 

void
umain(int argc, char **argv)
{
    int i, r;
    if (argc == 1) {
        fwritef(1, "cd: too few args");
        return;
    }

    if (strcmp(argv[i], ".") == 0) return;

    int path[256];
    if (strcmp(argv[i], "..") == 0) {
        curpath_get_parent(path);
        curpath_set(path);
        fwritef(1, "cd: %s", path);
        return;
    } else {
        if ((r = curpath_get(path)) < 0) {
            fwritef(1, "cd: cannot get environment var [curpath]");
            return;
        }
        strcat(path, argv[i]);
        int len = strlen(path);
        if (path[len - 1] != '/') strcat(path, "/");

        struct Stat st;
        r = stat(path, &st);

        if (r == -E_NOT_FOUND) fwritef(1, "cd: " RED([%s]) " not found\n", path);
        else if (r < 0) fwritef(1, "cd: cannot cd " RED([%s]) "\n", path);
        else if (!st.st_isdir) fwritef(1, "cd: %s is not directory\n", path);
        else {
            if ((r = curpath_set(path)) < 0) fwritef(1, "Environment var " RED([curpath]) "not found");
            fwritef(1, "curpath: %s", path);
        }
        return;
    }
}
