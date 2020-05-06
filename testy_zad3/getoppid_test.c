#include <stdio.h>
#include <unistd.h>

int main(void) {
    for (pid_t i = 1; i < 1000; ++i) {
        pid_t oppid = getoppid(i);
        if (oppid != -1) {
            printf("pid: %u, oppid: %u\n", i, oppid);
        }
    }
    return 0;
}

