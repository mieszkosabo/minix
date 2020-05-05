#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

// można zmieniać aż do 30000, jeśli dla małych wartości jest ok
#define CHECKRANGE 20

int main(void) {
    // pids range from 0 to 30k - 1
    pid_t invalid_pid = 30000;
    if (getoppid(invalid_pid) != 0) {
        printf("powinno się wypisać INVALID ARGUMENT albo coś podobnego\n");
        printf("getoppid error: %s\n", strerror(errno));
    }

    printf("Nic po tej linijce nie powinno się wypisać\n");
    for (int i = 0; i <= CHECKRANGE; i++) {
        pid_t res = getoppid(i);
        if (res == -1 && errno != EINVAL) {
            printf("przyps, jakiś dziwny error: %s\n", strerror(errno));
        }
        if (res >= 30000) {
            printf("przyps, prawdopodobnie wypisujesz ppid nieistniejącego procesu:\n");
            printf("pid: %d oppid: %u\n\n", i, getoppid(i));
        }
    }

    return 0;
}