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
	printf("Nie powinno być żadnego errora i C powinno zmienić rodzica\n");
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
					if (changeparent() != 0) {
						printf("przyps: %s\n", strerror(errno));
					}
					printf("Jestem C: %u, moj nowy rodzic: %u. oryginalny rodzic: %u\n", getpid(), 
				getppid(), getoppid(getpid()));
					return 0;
				default:
					printf("Jestem B idę spać i elo\n");
					sleep(3);
					printf("Jestem B obudziłem się i elo\n");
					return 0;
			}
		default:
			printf("Jestem A: %d i waituje teraz\n", getpid());
			if (wait(0) == -1) perror("Error in wait\n");
			return 0;
	}

        return 0;
}
