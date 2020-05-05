#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(int argc, char** argv) {
    pid_t parent_pid = getpid();
	pid_t gparent_pid = getppid();
    printf("Powinien się wypisać error EACCES i C nie zmieni rodzica na dziadka (bo pewnie będzie adopotowany przez init\n");
	printf("jestem A pid: %u\nA ppid: %u\n", parent_pid, 
		gparent_pid);
	
	switch(fork()){
		case -1:
			perror("fork");
			break;
		case 0:
			printf("Jestem B: %u, moj rodzic: %u. Teraz forkuję\n", getpid(), 
				getppid());
			switch(fork()){ 
				case -1:
					perror("fork");
					break;
				case 0:
					printf("Jestem C: %u, moj rodzic: %u. Zaraz zmienie rodzica\n", getpid(), 
				getppid());
                    sleep(1);
					if (changeparent() != 0) {
                        printf("changeparent error: %s\n", strerror(errno));
                    }
					printf("Jestem C: %u, moj nowy rodzic: %u. oryginalny rodzic: %u\n", getpid(), 
				getppid(), getoppid(getpid()));
					return 0;
				default:
					printf("Jestem B i zwalam bez waitowania C\n");
					return 0;
			}
		default:
			printf("Jestem A: %d i zwalam bez waitowania\n", getpid());
			return 0;
	}

        return 0;
}
