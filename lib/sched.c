#include <env.h>
#include <pmap.h>
#include <printf.h>

/* Overview:
 *  Implement simple round-robin scheduling.
 *
 *
 * Hints:
 *  1. The variable which is for counting should be defined as 'static'.
 *  2. Use variable 'env_sched_list', which is a pointer array.
 *  3. CANNOT use `return` statement!
 */
/*** exercise 3.14 ***/
#define cur_list env_sched_list[point]
#define nxt_list env_sched_list[!point]

void sched_yield(void) {
    static int count = 0; // remaining time slices of current env
    static int point = 0; // current env_sched_list index
    struct Env *nxt_env;

    if (--count <= 0 || curenv == NULL || curenv->env_status != ENV_RUNNABLE) {
        int has_nxt_env = 0;

        // find in cur_list
        while (!LIST_EMPTY(&cur_list)) {
            nxt_env = LIST_FIRST(&cur_list);
            if (nxt_env->env_status == ENV_RUNNABLE) {
                has_nxt_env = 1;
                break;
            }
            LIST_REMOVE(nxt_env, env_sched_link);
            LIST_INSERT_TAIL(&nxt_list, nxt_env, env_sched_link);
        }

        if (LIST_EMPTY(&cur_list)) point = !point;

        // find in nxt_list
        if (!has_nxt_env) {
            while (!LIST_EMPTY(&cur_list)) {
                nxt_env = LIST_FIRST(&cur_list);
                if (nxt_env->env_status == ENV_RUNNABLE) {
                    has_nxt_env = 1;
                    break;
                }
                LIST_REMOVE(nxt_env, env_sched_link);
                LIST_INSERT_TAIL(&nxt_list, nxt_env, env_sched_link);
            }

            if (LIST_EMPTY(&cur_list)) {
                panic("^^^^^No ENV Runnable!^^^^^");
            }
        }

        LIST_REMOVE(nxt_env, env_sched_link);
        LIST_INSERT_TAIL(&nxt_list, nxt_env, env_sched_link);
        count = nxt_env->env_pri;
        env_run(nxt_env);
    } else {
        env_run(curenv);
    }

    /*  hint:
     *  1. if (count==0), insert `e` into `env_sched_list[1-point]`
     *     using LIST_REMOVE and LIST_INSERT_TAIL.
     *  2. if (env_sched_list[point] is empty), point = 1 - point;
     *     then search through `env_sched_list[point]` for a runnable env `e`, 
     *     and set count = e->env_pri
     *  3. count--
     *  4. env_run()
     *
     *  functions or macros below may be used (not all):
     *  LIST_INSERT_TAIL, LIST_REMOVE, LIST_FIRST, LIST_EMPTY
     */
}

#undef cur_list
#undef nxt_list
